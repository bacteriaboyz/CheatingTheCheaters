#include <stddef.h>

#include "connectChk.h"
#include "map.h"

bool connectChkGraph(simBac *sim, errorCode *error)
{
    stackBac stack;

    stackInit(&stack, sim->num_bac, error);

    if (*error == MEM)
    {
        goto connectChk_error;
    }

    setBac visited;

    setInit(&visited, sim->num_bac, error);

    if (*error == MEM)
    {
        goto connectChk_stack_free;
    }

    stackPush(&stack, sim->graph.bacteria+LIMITS_MAX_BACT-1, error);

    if (*error == MEM)
    {
        goto connectChk_both_free;
    }

    do
    {
        nodeBac *current = stackPop(&stack);

        if (!setIsMember(&visited, current))
        {
            mapState state;

            mapInitMagic(&state, &current->neighbors);

            nodeBac *neighbor;

            mapMagical(&state, &neighbor, NULL);

            while (neighbor)
            {
                stackPush(&stack, neighbor, error);

                if (*error == MEM)
                {
                    goto connectChk_both_free;
                }

                mapMagical(&state, &neighbor, NULL);
            }

           setAdd(&visited, current, error);

        }

    } while (!stackIsEmpty(&stack));

    stackFree(&stack);

    if (setCard(&visited) == sim->num_bac)
    {
        setFree(&visited);

        return true;
    }

    setFree(&visited);

    return false;

connectChk_both_free:
    setFree(&visited);
connectChk_stack_free:
    stackFree(&stack);
connectChk_error:
    return false;
}
