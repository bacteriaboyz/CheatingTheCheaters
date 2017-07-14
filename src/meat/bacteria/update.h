#ifndef _UPDATE_H
#define _UPDATE_H

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
 * Updates the given node's probabilities and data
 * 
 * Arguments:   nodeBac to be updated
 * 
 * Returns:     void
 * 
 * Errors:      ?
 */

void updateNode(nodeBac *node);

#endif
