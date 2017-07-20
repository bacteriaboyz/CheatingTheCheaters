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
        for (cInt i=0; i<LIMITS_DIM; ++i) // loop across dimensions 
        {
            newNode->pos[i] = pos[i]; // assign each coordinate
        }
        updateNeiVol(newNode,sim); // update volume of neighborhood sphere
        newNode->num_r_n = 0; // reset producer neighbor counter
        newNode->c = sim->c_b; // initialize concentration for this node
        newNode->dProd = sim->param.r_d; 
            // default nearest neighbor as very far away
        nnAdd(&sim->buckets,newNode,err);
            // Add newNode to NN data struct
        if (*err != SUCCESS)
        {
            return NULL;
        }
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
        nnState state;
        nnInitMagic(&state, &sim->buckets,newNode,err); // init iterator
        if (*err != SUCCESS)
        {
            return NULL;
        }
        for (cInt i=0; i<LIMITS_BNEIGHBORS; ++i) 
            // while iteration of neighboring buckets not finished,
        {
            nnIterator(&state, &potNei); // advance bucket iterator

            if (potNei) // if this bucket is not empty,
            {
                nodeBac *n; // iterating node pointer
                mapState state;
                mapInitMagic(&state, potNei);
                mapMagical(&state, &n, NULL); // get first potential neighbor
                while (n) // while iteration not finished,
                {
                    cFloat d = distance(newNode,n,sim); 
                        // distance between both nodes
                    if (d < sim->param.r_d && n != newNode)
                        // if within neighborhood limits and neighbor is not self
                    {
                        cInt num_nei_prev = tableCard(&newNode->neighbors);
                            // Used to check if adding same bacterium                       
                        mapAddBacterium(&newNode->neighbors,n,d,err);
                            // add this potential neighbor to newNode's 
                                // neighborhood
                        if (*err != SUCCESS) // if there's an error
                        {
                            return NULL; // run away, run away
                        }
                        if (n->enz && \
                            num_nei_prev + 1 == tableCard(&newNode->neighbors))
                            // if new node is producer 
                            // and was not already a neighbor
                        {
                            ++newNode->num_r_n; 
                                // increase num producer neighbors
                            if (!newNode->enz) // if new node is not a producer
                            {
                                if (newNode->dProd > d) 
                                    // if this producer is closer than 
                                        // nearest neighbor,
                                {
                                    newNode->dProd = d; 
                                        // set as new distance
                                }
                            }
                        }

                        num_nei_prev = tableCard(&n->neighbors);
                            // Used to check if adding same bacterium
                        mapAddBacterium(&n->neighbors,newNode,d,err);
                            // add newNode to this potential neighbor's 
                                // neighborhood
                        if (*err != SUCCESS) // if there's an error
                        {
                            return NULL; // run away, run away
                        }
                        if (newNode->enz && \
                            num_nei_prev + 1 == tableCard(&n->neighbors))
                            // if new node is producer 
                            // and was not already a neighbor
                        {
                            ++n->num_r_n; // increase neighbor's producer 
                                            //neighbors
                            setAdd(&sim->graph.update_set,n,err);
                                // neighbor added to update set
                            if (*err != SUCCESS)
                            {
                                return NULL;
                            }

                            cFloat possibleNewD = \
                                distance(newNode,n,sim);
                                // [ab] due to new node
                            if ( possibleNewD < n->dProd )
                                // if this concentration is higher,
                            {
                                n->dProd = possibleNewD; // update [ab]
                            }
                        }
                    }

                    mapMagical(&state, &n, NULL); // move node iterator forward
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
        *err = OUT_OF_BACT; // we're in trouble
    }
        
    return newNode;
}
