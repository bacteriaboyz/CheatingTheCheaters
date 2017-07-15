#include <stdlib.h>
#include "update.h"

void updateNode(nodeBac *node, simBac *sim)
{
    if (!node->enz) // if the node is not a producer,
    {
        updatePHGT(node,sim); // update p(HGT) first (if enz, then invariant 0) 
        updatePABDie(node,sim); // and probability of dying due to ab at replic.
                                // (if enz, then invariant)
    }
    updatePARep(node,sim); // then all do probability of attempting replication
    updatePRep(node,sim); // use the last three probabilities to update p(rep)
    updatePDie(node,sim); // as well as p(die)
}
