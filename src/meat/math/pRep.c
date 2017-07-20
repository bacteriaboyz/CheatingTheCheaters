#include "pRep.h"

void updatePRep(nodeBac *node, simBac *sim)
{
    node->p_rep = node->p_a_r * ( 1.0 - node->p_a_d );
        // probability of attempting replication and not dying while trying
}
