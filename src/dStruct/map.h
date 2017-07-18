#ifndef _MAP_H
#define _MAP_H

#include "bucket.h"
#include "node.h"
#include "table.h"
#include "types.h"

typedef struct
{
    tableHash *table;

    cInt pos;
} mapState;

/*
 * Initializes a new bacterium map with the given length.
 * Possible errors: MEM
 */

void mapInitBacTable(tableHash *table, cInt len, errorCode *error);

/*
 * Adds a (bacterium, dist) pair to the map. If the bacterium already exists,
 * the dist value is overwritten.
 * Possible errors: MEM
 */

void mapAddBacterium(
                        tableHash *table,
                        nodeBac *bacterium,
                        cFloat dist,
                        errorCode *error
                    );
/*
 * Looks up a distance in the map. The value is only valid if there is no
 * error.
 * Possible errors: NOT_FOUND
 */

cFloat mapLookupBacterium(
                            tableHash *table,
                            nodeBac *bacterium,
                            errorCode *error
                         );

/*
 * Deletes a bacterium from the map.
 * Possible errors: MEM, NOT_FOUND
 */

void mapDelBacterium(tableHash *table, nodeBac *bacterium, errorCode *error);

/*
 * Initializes a state object for iteration.
 */

void mapInitMagic(mapState *state, tableHash *table);

/*
 * Provides the means of iterating over a map of bacteria (but not the means of
 * production). Writes out one (bacterium, dist) pair to the addresses provided
 * on each call. The pair (NULL, 0) is used to signal completion. The state
 * object should be initialized with mapInitMagic().
 */

void mapMagical(mapState *state, nodeBac **bacterium, cFloat *dist);

/*
 * Initializes a new bucket map with the given length.
 */

void mapInitBucketTable(tableHash *table, cInt len, errorCode *error);

/*
 * Adds a new (index, bucket) pair to tha map. You should not overwrite an
 * existing bucket, as that will lead to a memory leak.
 * Possible errors: MEM
 */

void mapAddBucket(
                    tableHash *table,
                    cInt idx,
                    bucketBac *bucket,
                    errorCode *error
                 );

/*
 * Looks up a bucket in the map. Returns NULL if not found.
 */

bucketBac *mapLookupBucket(tableHash *table, cInt idx);

/*
 * Deletes a bucket from the map. The bucket itself should be freed first.
 * Possible errors: MEM, NOT FOUND
 */

void mapDelBucket(tableHash *table, cInt idx, errorCode *error);

#endif
