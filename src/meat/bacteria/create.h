#ifndef _CREATE_H
#define _CREATE_H

#include "sim.h"
#include "map.h"
#include "update.h"
#include "dist.h"
#include "set.h"
#include "neighVol.h"

/*
 * Creates a new node with the given characteristics at the given position.
 * Reuses an unused slot in the graph if it can find one.
 * Adds the new node into its corresponding bucket.
 * Finds its neighbors, adds the new node to the neighbors' neighbor hashtables
 * and updates their neighbor counters.
 * 
 * Arguments:   cVec position of new node
 *              0,1 bit value if it produces enzyme
 *              simBac pointer to access everything
 *              errorCode pointer to error
 *  
 * Returns:     nodeBac pointer new node
 * 
 * Errors:      ?
 */

nodeBac *createNode(cVec pos, cInt isProducer, simBac *sim, errorCode *err);

#endif
