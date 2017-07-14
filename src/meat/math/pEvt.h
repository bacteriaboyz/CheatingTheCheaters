#ifndef _PEVT_H
#define _PEVT_H

#include "sim.h"
#include "types.h"
#include "graph.h"
#include "limits.h"
#include "node.h"
#include "hash.h"
#include "table.h"
#include "bucket.h"
#include "errors.h"
#include "stack.h"
#include "rng.h"
#include "nn.h"
#include "param.h"

/* 
 * Function updates event probability in t step of given bacterium 
 * 
 *  Arguments:  pointer to node struct to be modified
                pointer to sim  struct to access constants
 * 
 *  Returns:    void
 * 
 *  Errors:     ??
 */

void updatePEvt(nodeBac *node, simBac *sim);

#endif
