#ifndef _DIE_H
#define _DIE_H

#include "sim.h"
#include "update.h"
#include "map.h"
#include "set.h"
#include "dist.h"

/*  Function assigns nodeBac from graphBac struct as unused, and adds it to
 *  the graphBac dead stack in order to be reused by a new bacteria. If the 
 *  bacteria was resistant, it updates the fitness function of all its 
 *  neighbors.
 *
 *  Arguments:  pointer nodeBac struct to be killed
 *              simBac struct pointer to access everything
 *              error pointer (table and stack errors)
 * 
 *  Returns:    void
 *
 *  Errors:     ??
 */
void dieNode(nodeBac *node, simBac *sim, errorCode *err);

#endif
