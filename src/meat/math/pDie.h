#ifndef _PDIE_H
#define _PDIE_H

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
 * Function updates death probability in t step of given bacterium 
 * 
 *  Arguments:  pointer to node struct to be modified
                pointer to sim  struct to access constants
 * 
 *  Returns:    void
 * 
 *  Errors:     ??
 */

void updatePDie(nodeBac *node, simBac *sim);

#endif