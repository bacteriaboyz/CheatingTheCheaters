#include <stdlib.h>

#include "set.h"

bool setIsEmpty(setBac *set)
{
    return tableIsEmpty(set);
}

void setInit(setBac *set, cInt len, errorCode *error)
{
    tableInit(set, len, sizeof(nodeBac *), sizeof(int), error);
}

void setReset(setBac *set)
{
    tableReset(set);
}

void setAdd(setBac *set, nodeBac *bacterium, errorCode *error)
{
    int dummy = 0;

    tableAdd(set, TYPES_CBYTE(&bacterium), TYPES_CBYTE(&dummy), error);
}

bool setIsMember(setBac *set, nodeBac *bacterium)
{
    return tableLookup(set, TYPES_CBYTE(&bacterium)) != NULL;
}

void setDel(setBac *set, nodeBac *bacterium, errorCode *error)
{
    tableDel(set, TYPES_CBYTE(&bacterium), error);
}

void setFree(setBac *set)
{
    tableFree(set);
}
