#ifndef _STACK_H
#define _STACK_H

#include <stdbool.h>

#include "errors.h"
#include "types.h"

typedef struct
{
    void **data;

    cInt idx;

    cInt len;
} stackBac;

/*
 * Tests whether the stack is empty.
 */

bool stackIsEmpty(stackBac *stack);

/*
 * Initializes a new stack with the given length.
 * Possible errors: MEM
 */

void stackInit(stackBac *stack, cInt len, errorCode *error);

/*
 * Pushes a pointer onto the stack.
 * Possible errors: MEM
 */

void stackPush(stackBac *stack, void *ptr, errorCode *error);

/*
 * Pops a pointer from the stack. Returns NULL if stack is empty.
 */

void *stackPop(stackBac *stack);

/*
 * Frees the memory used by the stack.
 */

void stackFree(stackBac *stack);

#endif
