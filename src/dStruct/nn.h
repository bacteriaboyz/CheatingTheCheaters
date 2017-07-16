#ifndef _NN_H
#define _NN_H

#include "set.h"

typedef struct
{
    tableHash *bucketTable;

    cVec sides;

    cInt counts[LIMITS_DIM];
} nnBuckets;

/*
 * Computes the bucket coordinates of a bacterium given its physical
 * coordinates; writes them out to "coords".
 * Possible errors: INCONSISTENT
 */

void nnBucketCords(
                    nnBuckets *nn,
                    nodeBac *bacterium,
                    cInt *coords,
                    errorCode *error
                  );

void addToNN(nnBuckets *nn, nodeBac *node, cFloat radius);

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

#endif
