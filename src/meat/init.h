#ifndef _INIT_H
#define _INIT_H

#include "sim.h"

#include "abBlood.h"
#include "create.h"
#include "update.h"
#include "snapshot.h"
#include "limits.h"
#include "transform.h"

/* 
 * Function initializes simulation by reading input parameters into sim struct,
 * calculating remaining parameters, creating initial population of bacteria, 
 * and taking a snapshot of the result.
 *
 *  Arguments:  pointer to the simulation struct containing everything
 *              pointer to string containing parameter file address
 *              errorCode pointer to keep track of errors.
 *
 *  Returns:    void
 *
 *  Errors:     REJECT, INCONSISTENT, MEM, FILE_NOT_FOUND, MALFORMED_FILE,
 *              NUM_DOSES, ERR_CREATE_FILE, ERR_READ_FILE, PRINT_FAIL
**/

void initSim(simBac *sim, char *param_file, errorCode *err);

#endif
