#include "set.h"

bool setIsEmpty(setBac *set)
{
    return tableIsEmpty(set);
}

void setInit(setBac *set, cInt len, errorCode *error)
{
    tableInit(set, len, error);
}

void setAdd(setBac *set, nodeBac *bacterium, errorCode *error)
{
    tableAddBacterium(set, bacterium, 0, error);
}

bool setIsMember(setBac *set, nodeBac *bacterium)
{
    errorCode error;

    tableLookupBacterium(set, bacterium, &error);

    return error == SUCCESS;
}

void setDel(setBac *set, nodeBac *bacterium, errorCode *error)
{
    tableDelBacterium(set, bacterium, error);
}

void setFree(setBac *set)
{
    tableFree(set);
}
