#ifndef _SET_H
#define _SET_H

#include "node.h"
#include "table.h"

typedef tableHash setBac;

/*
 * Checks whether the set is empty.
 */

bool setIsEmpty(setBac *set);

/*
 * Initializes a new set with the given length.
 * Possible errors: MEM
 */

void setInit(setBac *set, cInt len, errorCode *error);

/*
 * Adds a bacterium to the set.
 * Possible errors: MEM
 */

void setAdd(setBac *set, nodeBac *bacterium, errorCode *error);

/*
 * Tests whether a given bacterium is in the set.
 */

bool setIsMember(setBac *set, nodeBac *bacterium);

/*
 * Deletes a bacterium from the set.
 * Possible errors: NOT_FOUND
 */

void setDel(setBac *set, nodeBac *bacterium, errorCode *error);

/*
 * Frees the memory used by the set.
 */

void setFree(setBac *set);

#endif
