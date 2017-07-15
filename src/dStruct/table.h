#ifndef _TABLE_H
#define _TABLE_H

#include <stdbool.h>

#include "errors.h"
#include "limits.h"
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

typedef struct
{
    cByte key[LIMITS_TABLE_ENTRY_SIZE];

    cByte val[LIMITS_TABLE_ENTRY_SIZE];

    cInt used : 1;
    cInt used_before : 1;
} tableSlot;

typedef struct
{
    tableSlot *slots;

    cInt key_len; // Length of key in bytes.

    cInt val_len; // Length of value in bytes.

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
 * Tests whether the table has been initialized (only works if uninitialized
 * tables are zeroed out).
 */

bool tableIsInit(tableHash *table);

/*
 * Initializes a new hash table with the given length.
 * Possible errors: MEM
 */

/*
 * Returns the cardinality (number of entries) of the table.
 */

cInt tableCard(tableHash *table);

void tableInit(
                tableHash *table,
                cInt table_len,
                cInt key_len,
                cInt val_len,
                errorCode *error
              );

/*
 * Clears the table while keeping the same internal size.
 */

void tableReset(tableHash *table);

/*
 * Adds an entry to the hash table. If the key already exists, the entry is
 * overwritten. "key_len" should be set to the size of the primitive key type.
 * Possible errors: MEM
 */

void tableAdd(tableHash *table, cByte *key, cByte *val, errorCode *error);

/*
 * Looks up a value in the hash table.
 * Possible errors: NOT_FOUND
 */

cByte *tableLookup(tableHash *table, cByte *key);

/*
 * Deletes an entry from the hash table.
 * Possible errors: NOT_FOUND
 */

void tableDel(tableHash *table, cByte *key, errorCode *error);

/*
 * Frees the memory used by the hash table.
 */

void tableFree(tableHash *table);

#endif
