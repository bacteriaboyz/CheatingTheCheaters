#ifndef _POPULATION_H
#define _POPULATION_H

#include "math.h"

#include "types.h"
#include "dStruct/node.h"
#include "dStruct/sim.h"

/** Function returns masking factor (probability of reproduction) for a given
*   node due to population density (number of neighbors).
* 
*   Arguments:  pointer to the nodeBac struct to be replicated
*               pointer to simulation struct, in order to access constants
*
*   Returns:    Floating point number (range 0-1) with masking value
*
*   Errors:     ??
**/
cFloat populationEff(*nodeBac node, *simBac sim);

#endif
