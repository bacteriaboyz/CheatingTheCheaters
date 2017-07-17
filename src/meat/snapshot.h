#ifndef _SNAPSHOT_H
#define _SNAPSHOT_H

#include "sim.h"

/*
 * This function creates our input file for the paraview program in VTK format.
 * This function also outputs the data to a csv file used for graphing separate
 * from the animation.
 * 
 * Arguments: 	A pointer to the simulation structure of type simBac. 
 * 
 * Returns: 	jack.
 *
 * Errors:		FILE_NOT_FOUND
 */
 
 void snapshotSim(simBac *sim, errorCode *err);
#endif