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

    for (cInt i = pos; i < internal_table->len; ++i)
    {
        tableSlot *slot = internal_table->slots + i;

        if (slot->used)
        {
            memcpy(bacterium, slot->key, sizeof(nodeBac *));
            memcpy(dist, slot->val, sizeof(cFloat));
            pos = i + i;
            return;
        }
    }

    *bacterium = NULL;
    *dist = 0;
}
