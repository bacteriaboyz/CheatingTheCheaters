#include "create.h"

nodeBac *createNode(cVec pos, cInt isProducer, graphBac *graph)
{
    nodeBac *newNode = stackPop(&graph->dead_stack); 
        // Check to see if there's an unused node
    if (!newNode) { // if there isn't...
        //TODO: create new node in sim->graph.bacteria?
    }
    
    // Assign new properties
    for (cInt i=0; i<3; i++) // loop across dimensions TODO: custom dims
    {
        newNode->pos[i] = pos[i]; // assign each coordinate
    }
    newNode->enz = isProducer; // assign enzyme production
    
    //TODO: Add newNode to bucket

    //TODO: get potential neighbors using frnn struct

    //TODO: iterate potential neighbors, 
    //

    updateNode(newNode);
    
    return newNode;
}
