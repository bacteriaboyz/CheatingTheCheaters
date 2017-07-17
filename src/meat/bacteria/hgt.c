#include <stdlib.h>
#include "hgt.h"

void hgtNode(nodeBac *node, simBac *sim, errorCode *err)
{
    // Set conditions that are now invariant:
    node->enz = 1; // make this node a producer
    node->p_hgt = 0; // probability of acquiring plasmid is now invariant at 0
    node->c = abConc(sim->param.r_c, sim); // set concentration at cell surface
    updatePABDie(node,sim); // update probability of AB-induced death
    
    nodeBac *n; // stores neighbor
    mapMagical(NULL,NULL,&node->neighbors); // initialize iterator
    for (cInt i=0; i < tableCard(&node->neighbors); i++) // iterate through neighbors
    {
        mapMagical(&n,NULL,NULL); // get next neighbor
        ++n->num_r_n; // one more resistant neighbor for this neighbor
       
        setAdd(&sim->graph.update_set,n,err); // update this neighbor's data
        if (*err != SUCCESS)
        {
            return;
        }
    }

    setAdd(&sim->graph.update_set,n,err); // update this node
}
