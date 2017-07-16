#include <string.h>

#include "map.h"

void mapInitBacTable(tableHash *table, cInt len, errorCode *error)
{
    tableInit(table, len, sizeof(nodeBac *), sizeof(cFloat), error);
}

void mapAddBacterium(
                        tableHash *table,
                        nodeBac *bacterium,
                        cFloat dist,
                        errorCode *error
                    )
{
    tableAdd(table, TYPES_CBYTE(&bacterium), TYPES_CBYTE(&dist), error);
}

cFloat mapLookupBacterium(
                            tableHash *table,
                            nodeBac *bacterium,
                            errorCode *error
                         )
{
    cFloat *val = (cFloat *)tableLookup(table, TYPES_CBYTE(&bacterium));

    if (val)
    {
        *error = SUCCESS;
        return *val;
    }

    *error = NOT_FOUND;
    return 0;
}

void mapDelBacterium(tableHash *table, nodeBac *bacterium, errorCode *error)
{
    tableDel(table, TYPES_CBYTE(&bacterium), error);
}

void mapMagical(nodeBac **bacterium, cFloat *dist, tableHash *table)
{
    static tableHash *internal_table;
    static cInt pos;

    if (table)
    {
        internal_table = table;
        pos = 0;
        return;
    }

    for (; pos < internal_table->len; ++pos)
    {
        tableSlot *slot = internal_table->slots + pos;

        if (slot->used)
        {
            if (bacterium)
            {
                memcpy(bacterium, slot->key, sizeof(nodeBac *));
            }

            if (dist)
            {
                memcpy(dist, slot->val, sizeof(cFloat));
            }

            ++pos;
            return;
        }
    }

    if (bacterium)
    {
        *bacterium = NULL;
    }

    if (dist)
    {
        *dist = 0;
    }
}

void mapInitBucketTable(tableHash *table, cInt len, errorCode *error)
{
    tableInit(table, len, sizeof(cInt), sizeof(bucketBac), error);
}

void mapAddBucket(
                    tableHash *table,
                    cInt idx,
                    bucketBac *bucket,
                    errorCode *error
                  )
{
    tableAdd(table, TYPES_CBYTE(&idx), TYPES_CBYTE(bucket), error);
}

bucketBac *mapLookupBucket(tableHash *table, cInt idx)
{
    return (bucketBac *)tableLookup(table, TYPES_CBYTE(&idx));
}

void mapDelBucket(tableHash *table, cInt idx, errorCode *error)
{
    tableDel(table, TYPES_CBYTE(&idx), error);
}
