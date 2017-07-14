#include "pABDie.h"

#include <math.h>

void updatePABDie(nodeBac *node, simBac *sim)
{
    node->p_a_d = 1.0 / ( 1.0 + pow( ( sim->param.c_h / node->c ), h ) );
        // Calculate probability using refitted Hill equation for dose response
}
