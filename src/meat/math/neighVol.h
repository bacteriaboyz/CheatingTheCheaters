#ifndef _NEIGHVOL_H
#define _NEIGHVOL_H

#include "sim.h"

/* 
 * Function updates volume of this node's neighborhood sphere. Sphere caps at
 * top and bottom of last dimension
 * 
 * Arguments:   pointer to node struct to be modified
 *              pointer to sim struct to access constants
 * 
 *  Returns:    void
 * 
 *  Errors:     ??
 */

void updateNeiVol(nodeBac *node, simBac *sim);

#endif
