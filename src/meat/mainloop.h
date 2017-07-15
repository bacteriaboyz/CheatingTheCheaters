#ifndef _MAINLOOP_H
#define _MAINLOOP_H

#include "sim.h"

#include "abBlood.h"
#include "create.h"
#include "die.h"
#include "replicate.h"
#include "hgt.h"
#include "update.h"

/* At each timestep:
 * Function iterates through all nodes on graph, adding them to replication,
 * kill or HGT stacks when pertinent. Then, it loops through each one of these
 * stacks calling the respective function in each case, each one of which adds
 * all nodes being created and the neighbors of the nodes created/destroyed to 
 * an update set. Finally, loops through the update set updating everyone's 
 * probabilities
 *
 *  Arguments:  pointer to the simulation struct containing everything
 *              errorCode pointer to keep track of errors.
 *
 *  Returns:    void
 *
 *  Errors:     REJECT, INCONSISTENT, MEM, NOT_FOUND
**/

void mainloopCall(simBac *sim, errorCode *err);

#endif
