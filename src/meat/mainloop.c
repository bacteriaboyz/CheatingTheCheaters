#include <stdbool.h>
#include "mainloop.h"

void mainloopSim(simBac *sim, errorCode *err)
{
    if (sim->param.output)
    {
        snapshotSim(sim,err); // write snapshot of graph struct to file 
    }
    while (sim->t < sim->param.t_max) // main time loop, once per time step
    { 
        cFloat prevAB = sim->c_b; // previous turn's AB concentration
        updateAB(sim); // Update blood antibiotic concentration, advance dosage
                        // if necessary
        
        sim->t += sim->param.t_s; // advance time tracker
       
        nodeBac *node; // temp var used to access stuff
 
        for (cInt i=0; i<LIMITS_MAX_BACT; i++) // loop across all bacteria
        {
            if (sim->graph.bacteria[i].used) // only operate on used bacteria
            {
                node = &sim->graph.bacteria[i]; // current node
                
                if (prevAB != sim->c_b || \
                    setIsMember( &sim->graph.update_set,node ) )
                    // if the blood ab has changed or there is some other 
                        // rason to update this node
                {
                    updateNode(node,sim); // dewit
                }

                cFloat r_1 = transformUnif(sim->state,0.0,1.0); // one random number
                if ( r_1 < node->p_rep ) // if replicating this time step
                {
                    stackPush(&sim->graph.rep_stack,node,err); // add to repl. stack
                }
                else if ( r_1 < node->p_rep + node->p_die) // if dying this t step
                {
                    stackPush(&sim->graph.die_stack,node,err); // add to die stack
                }
                else if ( r_1 < node->p_rep + node->p_die + node->p_hgt)
                    // if undergoing hgt this t step
                {
                    stackPush(&sim->graph.hgt_stack,node,err); // add to hgt stack
                }
            }
        }

        setReset(&sim->graph.update_set); // reset update set
        
        node = stackPop(&sim->graph.rep_stack); // get first element from stack
        while (node) // while node is not null
        {
            replicateNode(node,sim,err); // replicate this node
            if (*err != SUCCESS)
            {
                return;
            }
            node = stackPop(&sim->graph.rep_stack); // get first element from stack
        }
        
        node = stackPop(&sim->graph.die_stack); // get first element from stack
        while (node) // while node is not null
        {
            dieNode(node,sim,err); // kill this node
            if (*err != SUCCESS)
            {
                return;
            }
            node = stackPop(&sim->graph.die_stack); // get first element from stack
        }

        node = stackPop(&sim->graph.hgt_stack); // get first element from stack
        while (node) // while node is not null
        {
            hgtNode(node,sim,err); // HGT to this node
            if (*err != SUCCESS)
            {
                return;
            }
            node = stackPop(&sim->graph.hgt_stack); // get first element from stack
        }

        sim->t_last_snap += sim->param.t_s; // advance last snapshot timer
        
        if (sim->param.output && sim->t_last_snap >= sim->param.snap_freq)
            // if outputting to files and time since last snapshot is long enough
        {
            sim->t_last_snap = 1; // reset snapshot timer
            snapshotSim(sim,err); // write snapshot of graph struct to file
        }
    }
}
