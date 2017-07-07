#ifndef _REPRODUCTION_H
#define _REPRODUCTION_H

#include "math.h"

#include "types.h"
#include "dStruct/graph.h"
#include "dStruct/node.h"
#include "rng/transform.h"
#include "meat/fitness.h"

/** Function creates new nodeBac struct in a radius around the nodeBac struct 
*   whose index is passed as an argument. Assigns nodeback neighbors and all 
*   other fields of the nodeback struct. Updates fitness of all neighbors if 
*   the new bacteria is resistant.
*
*   Arguments:  pointer to the nodeBac struct to be replicated
*               graphbac struct pointer
*
*   Returns:    void
*
*   Errors:     ??
**/
void reproductionBac(nodeBac *node, graphBac *graph, simBac *sim, rngState rand_State);

#endif
