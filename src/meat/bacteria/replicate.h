#ifndef _REPLICATE_H
#define _REPLICATE_H

#include "sim.h"
#include "transform.h"
#include "errors.h"
#include "create.h"

/** Function creates new nodeBac struct in a radius around the nodeBac struct 
*   whose index is passed as an argument. 
*
*   Arguments:  pointer to the nodeBac struct to be replicated
*               simBac struct pointer
*               errorCode output errors
*
*   Returns:    void
*
*   Errors:     REJECT, INCONSISTENT, MEM
**/
void replicateNode(nodeBac *node, simBac *sim, errorCode *err);

#endif
