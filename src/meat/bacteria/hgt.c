#include <stdlib.h>
#include "hgt.h"

void hgtNode(nodeBac *node, simBac *sim, errorCode *err)
{
    node->enz = 1; // make this node a producer
    node->p_hgt = 0; // probability of acquiring plasmid is now 0
    
    nodeBac *n; // stores neighbor
    mapMagical(NULL,NULL,&node->neighbors); // initialize iterator
    for (cInt i=0; i < tableCard(&node->neighbors); i++) // iterate through neighbors
    {
        mapMagical(&n,NULL,NULL); // get next neighbor
        ++n->num_r_n; // one more resistant neighbor for this neighbor
       
        setAdd(&sim->graph.update_set,n,err); // update this neighbor's data
        if (err != SUCCESS)
        {
            return;
        }

         mapDelBacterium(&n->neighbors,node,err); // advance iterator
    }

    setAdd(&sim->graph.update_set,n,err); // update this node
}

