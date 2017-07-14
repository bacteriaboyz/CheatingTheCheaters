#ifndef _PREP_H
#define _PREP_H

#include "sim.h"

/* 
 * Function updates probability of replication in t step for node
 * 
 *  Arguments:  pointer to node struct to be modified
 *              pointer to sim struct to access constants
 * 
 *  Returns:    void
 * 
 *  Errors:     ??
 */

void updateRep(nodeBac *node, simBac *sim);

#endif
