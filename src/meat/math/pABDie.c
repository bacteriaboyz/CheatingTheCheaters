#include "pABDie.h"

#include <math.h>

void updatePABDie(nodeBac *node, simBac *sim)
{
    if (node->c == 0) // remove discontinuity
    {
        node->p_a_d = 0;
    }
    else
    {
        node->p_a_d = 1.0 / \
            ( 1.0 + pow( ( sim->param.c_h / \
            ( node->c + sim->param.c_c / 2.0) ), sim->param.h ) );
            // Calculate probability using refitted 
                // Hill equation for dose response
    }
}
