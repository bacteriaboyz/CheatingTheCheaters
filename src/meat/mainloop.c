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
        updateAB(sim); // Update blood antibiotic concentration, advance dosage
                        // if necessary

        nodeBac *node; // set and stack iteration variable
        mapState state;
        mapInitMagic(&state, &sim->graph.update_set); // init iterator on update
        mapMagical(&state, &node, NULL); // get first node to be updated
        while (node) // loop through all nodes to be updated
        {
            updateNode(node,sim); // update this node
            mapMagical(&state, &node, NULL); // get first node to be updated
        }
        
        sim->t += sim->param.t_s; // advance time tracker
        
        for (cInt i=0; i<LIMITS_MAX_BACT; i++) // loop across all bacteria
        {
            if (sim->graph.bacteria[i].used) // only operate on used bacteria
            {
                nodeBac *node = &sim->graph.bacteria[i]; // current node
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

        if (sim->param.output && sim->t_last_snap >= sim->param.snap_freq)
            // if outputting to files and time since last snapshot is long enough
        {
            sim->t_last_snap = 1; // reset snapshot timer
            snapshotSim(sim,err); // write snapshot of graph struct to file
        }
        else
        {
            sim->t_last_snap += sim->param.t_s; // advance last snapshot timer
        }
    }
}
