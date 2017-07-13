#ifndef _MAINLOOP_H
#define _MAINLOOP_H

#include "math.h"

#include "types.h"
#include "sim.h"
#include "graph.h"

/** Function iterates through all nodes on graph, calling reproduction and 
 *  death functions when pertinent.
 *
 *  Arguments:  pointer to the graphBac struct containing the nodes
 *              pointer to simulation struct, in order to access constants
 *              rngState pointer object to the random number generator state
 *
 *  Returns:    void
 *
 *  Errors:     ??
**/

cFloat mainloopCall(graphBac *graph, simBac *sim);

#endif
