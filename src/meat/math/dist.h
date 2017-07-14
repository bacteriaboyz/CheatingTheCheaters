#ifndef _DIST_H
#define _DIST_H

#include "node.h"
#include "types.h"
#include "hash.h"
#include "table.h"
#include "errors.h"
#include "limits.h"

/* 
 * Returns distance between two nodes
 * 
 * Arguments:   nodeBac pointer n1
 *              nodeBac pointer n2
 * 
 * Returns:     cFloat distance
 */

cFloat distance(nodeBac *n1, nodeBac *n2);

#endif
