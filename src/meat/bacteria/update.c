#include <stdlib.h>
#include "update.h"

void updateNode(nodeBac *node, simBac *sim)
{
    updatePHGT(node,sim); // update p(HGT) first
    updatePARep(node,sim); // as well as probability of attempting replication
    updatePABDie(node,sim); // and probability of dying due to ab at replic.
    updatePRep(node,sim); // use the last three probabilities to update p(rep)
    updatePDie(node,sim); // as well as p(die)
    updatePEvt(node,sim); // finally, update total evt probability with p(hgt),
                            // p(rep), and p(die)
}
