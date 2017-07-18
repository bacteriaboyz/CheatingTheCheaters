#include <stdlib.h>
#include "create.h"

nodeBac *createNode(cVec pos, cInt isProducer, simBac *sim, errorCode *err)
{
    nodeBac *newNode = stackPop(&sim->graph.dead_stack); 
        // Get an unused node

    if (newNode) // If there actually was a free slot...
    {
        // Assign new properties
        
        newNode->used = 1; // set used to true        
        for (cInt i=0; i<LIMITS_DIM; i++) // loop across dimensions 
        {
            newNode->pos[i] = pos[i]; // assign each coordinate
        }
        updateNeiVol(newNode,sim); // update volume of neighborhood sphere
        newNode->num_r_n = 0; // reset producer neighbor counter
        nnAdd(&sim->buckets,newNode,err);
            // Add newNode to NN data struct
        newNode->enz = isProducer; // assign enzyme production
        ++sim->num_bac; // stores number of bacteria
        if (isProducer)
        {
            ++sim->num_pro; // if bacteria is producer, advances that counter
            // Set conditions that are now invariant:
            newNode->p_hgt = 0; // probability of acquiring plasmid is now invariant at 0
            newNode->c = abConc(sim->param.r_c, sim); // set concentration at cell surface
            updatePABDie(newNode,sim); // update probability of AB-induced death

        }
         
        if (tableIsInit(&newNode->neighbors)) // if table has been initialized,
        {
            tableReset(&newNode->neighbors); // just reset it
        }
        else // if not,
        {
            mapInitBacTable(&newNode->neighbors,1,err); // init neighbor table
            if (*err != SUCCESS) // if there's an error
            {
                return NULL; // run away, run away
            }
        }
                        
        // Add neighbors and add self to neighbors
        
        setBac *potNei; // potential neighbors
        nnIterator(&sim->buckets,&potNei,newNode,err); // init iterator
        if (*err != SUCCESS)
        {
            return NULL;
        }
        for (cInt i=0; i<LIMITS_BNEIGHBORS; i++) 
            // while iteration of neighboring buckets not finished,
        {
            nnIterator(&sim->buckets,&potNei,NULL,err); // advance bucket iterator
            if (*err != SUCCESS)
            {
                return NULL;
            }
            if (potNei) // if this bucket is not empty,
            {
                nodeBac *n; // iterating node pointer
                mapMagical(NULL,NULL,potNei); // init iterator 
                mapMagical(&n,NULL,NULL); // get first potential neighbor
                while (n) // while iteration not finished,
                {
                    cFloat d = distance(newNode,n,sim); 
                        // distance between both nodes
                    if (d < sim->param.r_d && n != newNode) // if within neighborhood limits,
                    {
                        mapAddBacterium(&newNode->neighbors,n,d,err);
                            // add this potential neighbor to newNode's 
                                // neighborhood
                        if (*err != SUCCESS) // if there's an error
                        {
                            return NULL; // run away, run away
                        }
                        if (n->enz) // if neighbor is producer
                        {
                            ++newNode->num_r_n; 
                                // increase num producer neighbors
                            if (!newNode->enz) // if new node is not a producer
                            {
                                cFloat potC = abConc(d,sim); 
                                    // calculate concentration due to 
                                        // this neighbor
                                if (newNode->c > potC) 
                                    // if [ab] is less with this producer as 
                                        // nearest neighbor,
                                {
                                    newNode->c = potC; 
                                        // set as new concentration
                                }
                            }
                        }

                        mapAddBacterium(&n->neighbors,newNode,d,err);
                            // add newNode to this potential neighbor's 
                                // neighborhood
                        if (*err != SUCCESS) // if there's an error
                        {
                            return NULL; // run away, run away
                        }
                        if (newNode->enz) // if new node is producer
                        {
                            ++n->num_r_n; // increase neighbor's producer 
                                            //neighbors
                            setAdd(&sim->graph.update_set,n,err);
                                // neighbor added to update set
                            if (*err != SUCCESS)
                            {
                                return NULL;
                            }

                            cFloat possibleNewC = \
                                abConc(distance(newNode,n,sim),sim);
                                // [ab] due to new node
                            if ( possibleNewC < n->c )
                                // if this concentration is higher,
                            {
                                n->c = possibleNewC; // update [ab]
                            }
                        }
                    }

                    mapMagical(&n,NULL,NULL); // move node iterator forward
                }
            } 
        }
        
        // update this node
        setAdd(&sim->graph.update_set,newNode,err); // new node must be updated
        if (*err != SUCCESS)
        {
            return NULL;
        }

        *err = SUCCESS; // no errors here!
    }
    else // if there were no free nodes
    {
        *err = INCONSISTENT; // we're in trouble
    }
        
    return newNode;
}
