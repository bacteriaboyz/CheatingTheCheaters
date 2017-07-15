#ifndef _DIST_H
#define _DIST_H

#include "node.h"
#include "sim.h"

/* 
 * Returns distance between two nodes, wrapping around all dimensions except
 * the last one.
 * 
 * Arguments:   nodeBac pointer n1
 *              nodeBac pointer n2
 *              simBac object to access max size of all dimensions except last
 * 
 * Returns:     cFloat distance
 */

cFloat distance(nodeBac *n1, nodeBac *n2, simBac *sim);

#endif
