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
 * Tests whether the set has been initialized (only works if uninitialized sets
 * are zeroed out).
 */

bool setIsInit(setBac *set);

/*
 * Returns the cardinality (number of elements) of the set.
 */

cInt setCard(setBac *set);

/*
 * Initializes a new set with the given length.
 * Possible errors: MEM
 */

void setInit(setBac *set, cInt len, errorCode *error);

/*
 * Clears the set while keeping the same internal size.
 */

void setReset(setBac *set);

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
 * Possible errors: MEM, NOT_FOUND
 */

void setDel(setBac *set, nodeBac *bacterium, errorCode *error);

/*
 * Frees the memory used by the set.
 */

void setFree(setBac *set);

#endif
