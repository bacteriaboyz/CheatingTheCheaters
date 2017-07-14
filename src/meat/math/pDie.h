#ifndef _PDIE_H
#define _PDIE_H

#include "sim.h"

/* 
 * Function updates death probability in t step of given bacterium 
 * 
 *  Arguments:  pointer to node struct to be modified
                pointer to sim  struct to access constants
 * 
 *  Returns:    void
 * 
 *  Errors:     ??
 */

void updatePDie(nodeBac *node, simBac *sim);

#endif
