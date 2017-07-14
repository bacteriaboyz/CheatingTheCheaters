#ifndef _PHGT_H
#define _PHGT_H

#include "sim.h"

/* 
 * Function updates horizontal gene transfer probability in t step of given 
 * bacterium 
 * 
 * Arguments:   pointer to node struct to be modified
 *              pointer to sim  struct to access constants
 * 
 *  Returns:    void
 * 
 *  Errors:     ??
 */

void updatePHGT(nodeBac *node, simBac *sim);

#endif
