#ifndef _CLEANUP_H
#define _CLEANUP_H

#include "sim.h"

/*
 * Frees memory and closes files held by the simulation.
 */

void cleanupSim(simBac *sim);

#endif
