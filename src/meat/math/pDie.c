#include "pDie.h"

#include <math.h>

void updatePDie(nodeBac *node, simBac *sim)
{
    node->p_die = ( sim->param.gam_n * sim->param.t_s + \
        // probability of natural death this time step
        node->p_a_r * node->p_a_d  );
        // probability of attempting replication and dying in the process
}
