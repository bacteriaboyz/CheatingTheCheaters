#include "map.H"

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
