#ifndef _FITNESS_H
#define _FITNESS_H

#include "math.h"

#include "types.h"
#include "dStruct/graph.h"
#include "dStruct/node.h"
#include "meat/enzyme.h"
#include "meat/antibiotic.h"
#include "meat/population.h"

/** Function updates fitness (reproduction probability) of the given node, 
*   based on the concentration of enzyme and antibiotic at the given node.
*
*   Arguments:  pointer to the nodeBac struct to be updated.
*
*   Returns:    void
*
*   Errors:     ??
**/
void fitnessUpdate(nodeBac *node);

#endif
