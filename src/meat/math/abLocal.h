#ifndef _ABLOCAL_H
#define _ABLOCAL_H

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
 * Function returns concentration of antibiotic at a given distance from a 
 * single enzyme-producing, antibiotic degrading, resistant bacteria working
 * at full force.
 * 
 * Arguments:   cFloat distance at which to calculate
 *              pointer to simulation struct, in order to access constants
 * 
 *  Returns:    cFloat concentration
 * 
 *  Errors:     ??
 */

cFloat abConc(cFloat d, simBac *sim);

#endif
