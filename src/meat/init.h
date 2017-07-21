#ifndef _INIT_H
#define _INIT_H

#include <stdbool.h>

#include "sim.h"
#include "connectChk.h"

/* 
 * Function initializes simulation by reading input parameters into sim struct,
 * calculating remaining parameters, creating initial population of bacteria, 
 * and taking a snapshot of the result.
 *
 *  Arguments:  pointer to the simulation struct containing everything
 *              pointer to string conataining name of run
 *              pointer to string containing parameter file address
 *              boolean denoting if frame-by-frame output should be done
 *              errorCode pointer to keep track of errors.
 *
 *  Returns:    void
 *
 *  Errors:     REJECT, INCONSISTENT, MEM, FILE_NOT_FOUND, MALFORMED_FILE,
 *              NUM_DOSES, ERR_CREATE_FILE, ERR_READ_FILE, PRINT_FAIL
 *              OUT_OF_BACT
**/

void initSim(simBac *sim, char *name_run, char *param_file, bool output, errorCode *err);

#endif
