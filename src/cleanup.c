#include <stdio.h>
#include <stdlib.h>

#include "cleanup.h"
#include "limits.h"
#include "nn.h"
#include "set.h"
#include "stack.h"

void cleanupSim(simBac *sim)
{
    fclose(sim->t_series_file);

    free(sim->param.doses_t);
    free(sim->param.doses_c);

    nnFree(&sim->buckets);

    setFree(&sim->graph.update_set);

    stackFree(&sim->graph.rep_stack);
    stackFree(&sim->graph.die_stack);
    stackFree(&sim->graph.hgt_stack);
    stackFree(&sim->graph.dead_stack);

    for (cInt i = 0; i < LIMITS_MAX_BACT; ++i)
    {
        if (tableIsInit(&sim->graph.bacteria[i].neighbors))
        {
            tableFree(&sim->graph.bacteria[i].neighbors);
        }
    }
}
