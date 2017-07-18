#ifndef _CONNECT_CHK_H
#define _CONNECT_CHK_H

#include <stdbool.h>

#include "errors.h"
#include "sim.h"

/*
 * Checks whether the graph in "sim" is connected. Requires a used bacterium to
 * be present in the last slot of the array.
 * Possible errors: MEM
 */

bool connectChkGraph(simBac *sim, errorCode *error);

#endif
