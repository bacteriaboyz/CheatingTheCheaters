#include <string.h>

#include "errors.h"
#include "limits.h"
#include "rng.h"
#include "setup.h"

static void setupInitStructs(simBac *sim, errorCode *error)
{
    stackInit(&sim->graph.rep_stack, LIMITS_MAX_BACT, error);

    if (*error == MEM)
    {
        return;
    }

    stackInit(&sim->graph.die_stack, LIMITS_MAX_BACT, error);

    if (*error == MEM)
    {
        goto sis_jmp4;
    }

    stackInit(&sim->graph.hgt_stack, LIMITS_MAX_BACT, error);

    if (*error == MEM)
    {
        goto sis_jmp3;
    }

    stackInit(&sim->graph.dead_stack, LIMITS_MAX_BACT, error);

    if (*error == MEM)
    {
        goto sis_jmp2;
    }

    setInit(&sim->graph.update_set, LIMITS_MAX_BACT, error);

    if (*error == MEM)
    {
        goto sis_jmp1;
    }

    *error = SUCCESS;
    return;

sis_jmp1:
    stackFree(&sim->graph.dead_stack);
sis_jmp2:
    stackFree(&sim->graph.hgt_stack);
sis_jmp3:
    stackFree(&sim->graph.die_stack);
sis_jmp4:
    stackFree(&sim->graph.rep_stack);
}

void setupSim(simBac *sim, cByte *phrase, errorCode *error)
{
    memset(sim, 0, sizeof(simBac));

    rngInitState(sim->state, phrase);

    setupInitStructs(sim, error);
}
