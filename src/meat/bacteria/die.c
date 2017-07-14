#include "die.h"

void dieNode(nodeBac *node, graphBac *graph)
{
   node->used = 0; // list node as unused

    if (node->enz) // if node was producer,
    {
        nodeBac *n; // stores neighbor
        cFloat d; // stores distance
        mapMagical(&n,&d,&node->neighbors); // initialize iterator
        for (cInt i=0; i < node->num_nei; i++) // iterate through neighbors
        {
            mapMagical(&n,&d,&node->neighbors); // get next neighbor
            --n->num_nei; // one less neighbor
            //TODO: remove node from neighbors of n
            
            if (node->enz) // if node was resistance
            {
                --n->num_r_n; // one less resistant neighbor
                updateNode(n); // update this neighbor's data
            }
        }
    }
    
    errorCode err; // save output of stack method
    stackPush(&graph->dead_stack,node,&err); // add node to dead stack for reuse
    //TODO: error?
}
