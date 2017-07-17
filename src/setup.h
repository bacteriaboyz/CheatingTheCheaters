#ifndef _SETUP_H
#define _SETUP_H

#include "sim.h"

/*
 * Allocates memory for the simulation but does not initialize anything.
 */

void setupSim(simBac *sim, cByte *phrase, errorCode *error);

#endif
