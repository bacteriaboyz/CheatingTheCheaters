#include "create.h"

nodeBac *createNode(cVec pos, cInt isProducer, simBac *sim, errorCode *err)
{
    nodeBac *newNode = stackPop(&sim->graph.dead_stack); 
        // Get an unused node

    if (n) // If there actually was a free slot...
    {

        // Assign new properties
        for (cInt i=0; i<LIMITS_DIM; i++) // loop across dimensions 
        {
            newNode->pos[i] = pos[i]; // assign each coordinate
        }

        newNode->enz = isProducer; // assign enzyme production
        mapInitBacTable(&newNode->neighbors,1,err); // init neighbor table
        if (err != SUCCESS) // if there's an error
        {
            return NULL; // run away, run away
        }

        addToNN(newNode,sim->param.r_d); // Add newNode to NN data struct //TODO: correct function name

        
        setBac *potNei; // potential neighbors
        nnIterator(NULL,newNode); // init iterator //TODO: correct function name
        nnIterator(&potNei,NULL); // get first set //TODO: correct function name
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
                    mapAddBacterium(&n->neighbors,newNode,d,err);
                        // add newNode to this potential neighbor's neighborhood
                    if (err != SUCCESS) // if there's an error
                    {
                        return NULL; // run away, run away
                    }
                }

                mapMagical(&n,NULL,NULL); // move node iterator forward
            }

            nnIterator(&potNei,NULL); // advance bucket iterator //TODO: correct function name
        }

        updateNode(newNode);

    }
    else
    {
        *err = INCONSISTENT; // we're in trouble
    }
        
    return newNode;
}
