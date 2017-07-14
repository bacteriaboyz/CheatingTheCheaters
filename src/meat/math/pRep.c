#include "pRep.h"

void updateRep(nodeBac *node, simBac *sim)
{
    node->p_rep = node->p_a_r * ( 1.0 - node->p_a_d ) * \
            // probability of attempting replication and not die trying
        ( 1.0 - sim->param.t_s * sim->param.gam_n ) * \
            // times probability of not dying naturally in time step
        ( 1.0 - node->p_hgt );
            // times probability of not undergoing hgt
}
