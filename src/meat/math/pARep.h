#ifndef _PAREP_H
#define _PAREP_H

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
 * Function updates probability of attempting replication in t step for node
 * 
 *  Arguments:  pointer to node struct to be modified
                pointer to sim  struct to access constants
 * 
 *  Returns:    void
 * 
 *  Errors:     ??
 */

void updatePArep(nodeBac *node, simBac *sim);

#endif
