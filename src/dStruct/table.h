#ifndef _TABLE_H
#define _TABLE_H

#include <stdbool.h>

#include "bucket.h"
#include "errors.h"
#include "node.h"
#include "types.h"

static const cInt table_sizes[] =
{
    2,
    5,
    11,
    23,
    47,
    97,
    197,
    397,
    797,
    1597,
    3203,
    6421,
    12853,
    25717,
    51437,
    102877,
    205759,
    411527,
    823117,
    1646237,
    3292489,
    6584983,
    13169977,
    26339969,
    52679969,
    105359939,
    210719881,
    421439783,
    842879579,
    1685759167,
    3371518343
};

static const cInt table_num_sizes = sizeof(table_sizes) / sizeof(cInt);

typedef union
{
    cInt idx;

    nodeBac *bacterium;
} tableKeyData;

typedef struct
{
    enum
    {
        INDEX,
        BACTERIUM
    } type;

    tableKeyData data;

} tableKey;

typedef union
{
    bucketBac *bucket;

    cFloat dist;
} tableValData;

typedef struct
{
    enum
    {
        BUCKET,
        DISTANCE
    } type;

    tableValData data;

} tableVal;

typedef struct
{
    tableKey key;

    tableVal val;

    cInt used : 1;
    cInt used_before : 1;
} tableSlot;

typedef struct
{
    tableSlot *slots;

    cInt num; // Number of used entries. Should be <= 50% of capacity.

    cInt num_ghosts; // Number of previously deleted entries.

    cInt len; // Total number of slots.

    cInt len_idx; // Index of size in prime table.
} tableHash;

/*
 * Tests whether the table is empty.
 */

bool tableIsEmpty(tableHash *table);

/*
 * Initializes a new hash table with the given length.
 * Possible errors: MEM
 */

void tableInit(tableHash *table, cInt len, errorCode *error);

/*
 * Adds an entry to the hash table. If the key already exists, the entry is
 * overwritten. "key_len" should be set to the size of the primitive key type.
 * Possible errors: MEM
 */

void tableAdd(
                tableHash *table,
                tableKey key,
                tableVal val,
                cInt key_len,
                errorCode *error
             );

// Use these functions instead for everyday purposes:

void tableAddBucket(
                    tableHash *table,
                    cInt idx,
                    bucketBac *bucket,
                    errorCode *error
                   );

void tableAddBacterium(
                        tableHash *table,
                        nodeBac *bacterium,
                        cFloat dist,
                        errorCode *error
                      );

/*
 * Looks up a value in the hash table.
 * Possible errors: NOT_FOUND
 */

tableVal tableLookup(
                        tableHash *table,
                        tableKey key,
                        cInt key_len,
                        errorCode *error
                    );

// Use these functions instead for everyday purposes:

bucketBac *tableLookupBucket(tableHash *table, cInt idx, errorCode *error);

cFloat tableLookupBacterium(
                            tableHash *table,
                            nodeBac *bacterium,
                            errorCode *error
                           );


/*
 * Deletes an entry from the hash table.
 * Possible errors: NOT_FOUND
 */

void tableDel(tableHash *table, tableKey key, cInt key_len, errorCode *error);

// Use these functions instead for everyday purposes:

void tableDelBucket(tableHash *table, cInt idx, errorCode *error);

void tableDelBacterium(tableHash *table, nodeBac *bacterium, errorCode *error);

/*
 * Frees the memory used by the hash table.
 */

void tableFree(tableHash *table);

#endif
