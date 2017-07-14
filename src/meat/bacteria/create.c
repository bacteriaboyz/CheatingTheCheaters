#include <stdlib.h>
#include "create.h"

nodeBac *createNode(cVec pos, cInt isProducer, simBac *sim, errorCode *err)
{
    nodeBac *newNode = stackPop(&sim->graph.dead_stack); 
        // Get an unused node

    if (newNode) // If there actually was a free slot...
    {

        // Assign new properties
        for (cInt i=0; i<LIMITS_DIM; i++) // loop across dimensions 
        {
            newNode->pos[i] = pos[i]; // assign each coordinate
        }

        newNode->enz = isProducer; // assign enzyme production
        if (tableIsInit(&newNode->neighbors)) // if table has been initialized,
        {
            tableReset(&newNode->neighbors); // just reset it
        }
        else // if not,
        {
            mapInitBacTable(&newNode->neighbors,1,err); // init neighbor table
            if (err != SUCCESS) // if there's an error
            {
                return NULL; // run away, run away
            }
        }

        newNode->num_nei = 0; // reset neighbor counter
        newNode->num_r_n = 0; // reset producer neighbor counter

         // Add newNode to NN data struct
        addToNN(newNode,sim->param.r_d);
        
        // Add neighbors and add self to neighbors
        setBac *potNei; // potential neighbors
        nnIterator(NULL,newNode); // init iterator
        nnIterator(&potNei,NULL); // get first set
        while (potNei) // while iteration of neighboring buckets not finished,
        {
            nodeBac *n; // iterating node pointer
            mapMagical(NULL,NULL,potNei); // init iterator 
            mapMagical(&n,NULL,NULL); // get first potential neighbor
            while (n) // while iteration not finished,
            {
                cFloat d = distance(newNode,n); // distance between both nodes
                if (d < sim->param.r_d) // if within nieghborhood limits,
                {
                    mapAddBacterium(&newNode->neighbors,n,d,err);
                        // add this potential neighbor to newNode's neighborhood
                    if (err != SUCCESS) // if there's an error
                    {
                        return NULL; // run away, run away
                    }
                    ++newNode->num_nei; // increase num neighbors counter
                    if (n->enz) // if neighbor is producer
                    {
                        ++newNode->num_r_n; // increase num producer neighbors
                    }

                    mapAddBacterium(&n->neighbors,newNode,d,err);
                        // add newNode to this potential neighbor's neighborhood
                    if (err != SUCCESS) // if there's an error
                    {
                        return NULL; // run away, run away
                    }
                    ++n->num_nei; // increase neighbor's num neighbors counter
                    if (newNode->enz) // if new node is producer
                    {
                        ++n->num_r_n; // increase neighbor's producer neighbors
                        setAdd(sim->graph.update_set,n,err);
                            // neighbor added to update set
                        if (err != SUCCESS))
                        {
                            return NULL;
                        }
                    }
                }

                mapMagical(&n,NULL,NULL); // move node iterator forward
            }

            nnIterator(&potNei,NULL); // advance bucket iterator
        }
        
        setAdd(sim->graph.update_set,newNode,err); // new node must be updated
        if (err != SUCCESS))
        {
            return NULL;
        }
    }
    else
    {
        *err = INCONSISTENT; // we're in trouble
    }
        
    return newNode;
}
