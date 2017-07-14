#ifndef _ABPDIE_H
#define _ABPDIE_H

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
 * Function updates death probability at replication due to antibiotic for 
 * given bacterium 
 * 
 *  Arguments:  pointer to node struct to be modified
 *              pointer to sim  struct to access constants
 * 
 *  Returns:    void
 * 
 *  Errors:     ??
 */

void updateABPDie(nodeBac *node, simBac *sim);

#endif
