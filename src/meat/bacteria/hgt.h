#ifndef _HGT_H
#define _HGT_H

#include "sim.h"
#include "update.h"
#include "map.h"

/* Function converts non-producer bacteria to a producer, and updates its
 * neighbors accordingly
 *
 *  Arguments:  pointer nodeBac struct to be killed
 *              simBac struct pointer to access everything
 *              error pointer (table and stack errors)
 * 
 *  Returns:    void
 *
 *  Errors:     ??
 */
void hgtNode(nodeBac *node, simBac *sim, errorCode *err);

#endif
