#include <string.h>

#include "rng.h"
#include "setup.h"

void setupSim(simBac *sim, char *phrase)
{
    memset(sim, 0, sizeof(simBac));

    rngInitState(sim->state, phrase);
}
