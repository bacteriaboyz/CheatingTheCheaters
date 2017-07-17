#ifndef _NN_H
#define _NN_H

#include "set.h"

typedef struct
{
    tableHash bucketTable;

    cVec sides;

    cInt counts[LIMITS_DIM];
} nnBuckets;


/*
 * Initializes the fixed-radius near neighbors structure. Like magnets, no one
 * is entirely sure how it works. Requires a vector describing the dimensions
 * of each bucket and bucket counts along each dimension in the simulation
 * space.
 * Possible errors: MEM
 */

void nnInit(nnBuckets *nn, cVec sides, cInt *counts, errorCode *error);

/*
 * Adds a bacterium to the FRNN structure.
 * Possible errors: INCONSISTENT, MEM
 */

void nnAdd(nnBuckets *nn, nodeBac *bacterium, errorCode *error);

/*
 * Deletes a bacterium from the FRNN structure.
 * Possible errors: INCONSISTENT, MEM
 */

void nnDel(nnBuckets *nn, nodeBac *bacterium, errorCode *error);

/*
 * Returns the bucket a bacterium is in and all adjacent ones for locating all
 * fixed-radius near neighbors. It has the same general operation as
 * mapMagical(). It should be called LIMITS_BNEIGHBORS times after
 * initialization, as it may output NULL when the adjacent bucket contains no
 * bacteria.
 * Possible errors: INCONSISTENT
 */

void nnIterator(
                nnBuckets *nn,
                setBac **out,
                nodeBac *bacterium,
                errorCode *error
               );

/*
 * Frees the FRNN structure.
 */

void nnFree(nnBuckets *nn);

#endif
