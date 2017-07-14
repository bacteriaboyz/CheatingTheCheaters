#ifndef _PAREP_H
#define _PAREP_H

#include "sim.h"
#include "abLocal.h"
#include "map.h"

/* 
 * Function updates probability of attempting replication in t step for node
 * 
 *  Arguments:  pointer to node struct to be modified
 *              pointer to sim struct to access constants
 * 
 *  Returns:    void
 * 
 *  Errors:     ??
 */

void updatePARep(nodeBac *node, simBac *sim);

#endif
