#ifndef _UPDATE_H
#define _UPDATE_H

#include "sim.h"
#include "pHGT.h"
#include "pARep.h"
#include "pABDie.h"
#include "pRep.h"
#include "pDie.h"
#include "pEvt.h"

/*
 * Updates the given node's probabilities and data
 * 
 * Arguments:   nodeBac to be updated
 *              simBac to access all constants
 * 
 * Returns:     void
 * 
 * Errors:      ?
 */

void updateNode(nodeBac *node, simBac *sim);

#endif
