#include <stdlib.h>

#include "stack.h"

bool stackIsEmpty(stackBac *stack)
{
    return stack->idx == 0;
}

void stackInit(stackBac *stack, cInt len, errorCode *error)
{
    if (len == 0 || !(stack->data = malloc((len + 1) * sizeof(void *))))
    {
        *error = MEM;
        return;
    }

    stack->idx = 0;
    stack->len = len;

    *error = SUCCESS;
}

void stackReset(stackBac *stack)
{
    stack->idx = 0;
}

void stackPush(stackBac *stack, void *ptr, errorCode *error)
{
    if (++stack->idx == stack->len)
    {
        void **new_data = realloc(
                                        stack->data,
                                        (stack->len *= 2) * sizeof(void *)
                                    );

        if (!new_data)
        {
            *error = MEM;
            return;
        }

        stack->data = new_data;
    }

    stack->data[stack->idx] = ptr;
}

void *stackPop(stackBac *stack)
{
    if (stack->idx == 0)
    {
        return NULL;
    }

    return stack->data[stack->idx--];
}

void stackFree(stackBac *stack)
{
    free(stack->data);
}
