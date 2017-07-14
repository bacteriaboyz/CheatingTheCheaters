#ifndef _DIE_H
#define _DIE_H

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

#include "update.h"
#include "map.h"

/*  Function assigns nodeBac from graphBac struct as unused, and adds it to
 *  the graphBac dead stack in order to be reused by a new bacteria. If the 
 *  bacteria was resistant, it updates the fitness function of all its 
 *  neighbors.
 *
 *  Arguments:  pointer nodeBac struct to be killed
 *              graphbac struct pointer 
 *
 *  Returns:    void
 *
 *  Errors:     ??
 */
void dieNode(nodeBac *node, graphBac *graph);

#endif
