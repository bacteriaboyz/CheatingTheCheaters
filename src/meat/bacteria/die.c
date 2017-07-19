#include <stdlib.h>
#include "die.h"

void dieNode(nodeBac *node, simBac *sim, errorCode *err)
{
    node->used = 0; // list node as unused

    --sim->num_bac; // reduces number of bacteria
    if (node->enz)
    {
        --sim->num_pro; // if node was producer, reduce that counter
    }

    nodeBac *n; // stores neighbor
    mapState state1, state2;
    mapInitMagic(&state1, &node->neighbors); // initialize iterator
    for (cInt i=0; i < tableCard(&node->neighbors); ++i)
        // iterate through neighbors
    {
        mapMagical(&state1, &n, NULL); // get next neighbor

        if (n != node) // if neighbor is not self,
        {
            mapDelBacterium(&n->neighbors,node,err);
                // delete this node from neighbor's neighbor array
            if (*err != SUCCESS) // if there's an error
            {
                return; // run away, run away
            }

            if (node->enz) // if dead node was producer,
            {
                --n->num_r_n; // neighbor has one less resistant neighbor
                setAdd(&sim->graph.update_set,n,err);
                    // update this neighbor's data
                if (*err != SUCCESS)
                {
                    return;
                }

                if ( abConc( distance( node,n,sim ) , sim ) <= n->c )
                    // if this node was this neighbor's closest producer
                {
                    nodeBac *n_n; // iterating node pointer
                    cFloat d; // iterating distance
                    cFloat min_d = sim->param.r_d;
                        // minimum distance to a producer default is max value
                    mapInitMagic(&state2, &node->neighbors); // init iterator
                    for (cInt i=0; i<tableCard(&node->neighbors); i++)
                        // loop through all nb's
                    {
                        mapMagical(&state2, &n_n, &d); // get next element
                        if (n_n != n && d < min_d) // if neighbor is not self
                                                    // and new min
                        {
                            min_d = d; // if new min, set
                        }
                    }

                    n->c = abConc(d,sim); // set new concentration of antibiotic
                                            // at this neighbor
                }
            }
        }
    }

    stackPush(&sim->graph.dead_stack,node,err); // add node to dead stack for reuse
    // if there's an error here, the function's already done anyway
}
