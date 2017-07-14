#include "pEvt.h"

void updatePEvt(nodeBac *node, simBac *sim)
{
    node->p_evt = node->p_hgt + node->p_die + node->p_rep;
}

