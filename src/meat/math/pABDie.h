#ifndef _ABPDIE_H
#define _ABPDIE_H

#include "sim.h"

/* 
 * Function updates death probability at replication due to antibiotic for 
 * given bacterium 
 * 
 *  Arguments:  pointer to node struct to be modified
 *              pointer to sim  struct to access constants
 * 
 *  Returns:    void
 * 
 *  Errors:     ??
 */

void updateABPDie(nodeBac *node, simBac *sim);

#endif
