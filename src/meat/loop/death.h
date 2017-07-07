#ifndef _DEATH_H
#define _DEATH_H

#include "types.h"
#include "dStruct/graph.h"
#include "dStruct/node.h"
#include "meat/fitness.h"

/*  Function assigns nodeBac from graphBac struct as unused, and adds its index 
 *  inside the graphBac stack in order to be reused by a new bacteria. If the 
 *  bacteria was resistant, it updates the fitness function of all its 
 *  neighbors.
 *
 *  Arguments:  index of nodeBac struct to be killed inside graphBac's bacteria
 *                  array.
 *              graphbac struct pointer 
 *
 *  Returns:    void
 *
 *  Errors:     ??
 */
void deathBac(cInt idx, *graphBac graph);

#endif
