#ifndef _ANTIBIOTIC_H
#define _ANTIBIOTIC_H

#include "math.h"

#include "types.h"
#include "dStruct/node.h"
#include "dStruct/sim.h"
#include "meat/enzyme.h"

/** Function returns masking factor (probability of reproduction) for a given
*   node due to effective antibiotic concentration at node, taking 
*   into account concentration of enzyme.
* 
*   Arguments:  pointer to the nodeBac struct to be replicated
*               pointer to simulation struct, in order to access constants
*
*   Returns:    Floating point number (range 0-1) with masking value
*
*   Errors:     ??
**/
cFloat antibioticEff(nodeBac *node, simBac *sim);

#endif
