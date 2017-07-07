#ifndef _ENZYME_H
#define _ENZYME_H

#include "math.h"

#include "types.h"
#include "dStruct/node.h"
#include "dStruct/sim.h"

/** Function returns enzyme concentration at the position of a given bacteria
*   by adding the concentrations due to the neighboring producer bacteria.
* 
*   Arguments:  pointer to the nodeBac struct to be replicated
*               pointer to simulation struct, in order to access constants
*
*   Returns:    Floating point number with the node's enzyme concentration
*
*   Errors:     ??
**/
cFloat enzymeConc(nodeBac *node, simBac *sim);

#endif
