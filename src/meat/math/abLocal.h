#ifndef _ABLOCAL_H
#define _ABLOCAL_H

#include "sim.h"

/* 
 * Function returns concentration of antibiotic at a given distance from a 
 * single enzyme-producing, antibiotic degrading, resistant bacteria working
 * at full force.
 * 
 * Arguments:   cFloat distance at which to calculate
 *              pointer to simulation struct, in order to access constants
 * 
 *  Returns:    cFloat concentration
 * 
 *  Errors:     ??
 */

cFloat abConc(cFloat d, simBac *sim);

#endif
