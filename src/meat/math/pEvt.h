#ifndef _PEVT_H
#define _PEVT_H

#include "sim.h"

/* 
 * Function updates event probability in t step of given bacterium 
 * 
 *  Arguments:  pointer to node struct to be modified
                pointer to sim  struct to access constants
 * 
 *  Returns:    void
 * 
 *  Errors:     ??
 */

void updatePEvt(nodeBac *node, simBac *sim);

#endif
