#ifndef _ABBLOOD_H
#define _ABBLOOD_H

#include "sim.h"

/* 
 * Function updates concentration of antibiotic in blood according to renal
 * renal clearance and new doses. 
 * 
 *  Arguments:  pointer to simulation struct, in order to access constants
 * 
 *  Returns:    void
 * 
 *  Errors:     ??
 */

void updateAB(simBac *sim);

#endif
