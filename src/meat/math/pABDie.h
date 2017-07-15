#ifndef _PABDIE_H
#define _PABDIE_H

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

void updatePABDie(nodeBac *node, simBac *sim);

#endif
