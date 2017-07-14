#ifndef _MAP_H
#define _MAP_H

#include "bucket.h"
#include "node.h"
#include "table.h"
#include "types.h"

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
 * Possible errors: NOT_FOUND
 */

void mapDelBacterium(tableHash *table, nodeBac *bacterium, errorCode *error);

/*
 * Provides the means of iterating over a map of bacteria (but not the means of
 * production). To initialize the iterator, it should be called with the first
 * two arguments NULL and the third argument containing the address of the
 * table. After that, it should be called with the third argument NULL and the
 * first two arguments containing addresses where the (bacterium, dist) pairs
 * will be written out. One it's reached then end of the table, it will write
 * out (NULL, 0) on each call.
 */

void mapMagical(nodeBac **bacterium, cFloat *dist, tableHash *table);

#endif
