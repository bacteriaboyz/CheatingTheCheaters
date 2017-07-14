#ifndef _ABBLOOD_H
#define _ABBLOOD_H

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
 * Function updates concentration of antibiotic in blood according to renal
 * renal clearance and new doses. 
 * 
 *  Arguments:  pointer to simulation struct, in order to access constants
 * 
 *  Returns:    void
 * 
 *  Errors:     ??
 */

void updateAB(simBac *sim);

#endif
