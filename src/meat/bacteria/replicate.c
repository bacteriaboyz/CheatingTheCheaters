#include "replicate.h"

void replicateBac(nodeBac *node, simBac *sim, errorCode *err)
{
    cInt limit_iter = 10000; // iteration limit for rejection sampling
    cInt iterChk = 0; // check iteration number
    cVec pos; // will store coordinates of new bacteria
    transformBall(sim->state,sim->param.d_bac,node->pos,pos,err);
        // sample from ball
    if (err != SUCCESS)
    {
        return;
    }

    while ( (pos[LIMITS_DIM-1] < 0 || pos[LIMITS_DIM-1] > sim->param.x_max ) \
        && iterChk < limit_iter )
        // if last coordinate is outside bounds of simulation or beyond max iter
    {
        transformBall(sim->state,sim->param.d_bac,node->pos,pos,err);
            // sample from ball
        ++iterChk; // advance counter
        if (err != SUCCESS)
        {
            return;
        }
    }
    if (iterChk > limit_iter) // if surpassed iter limit,
    {
        *err = REJECT; // throw tantrum
        return;
    }

    for (cInt i=0; i<LIMITS_DIM-1; i++) // iterate through all dims except last
    {
        if (pos[i] < 0) // if out of bounds on bottom,
        {
            pos[i] += sim->param.x_max; // wrap around bottom
        }
        else if (pos[i] > sim->param.x_max) // if out of bounds on top,
        {
            pos[i] -= sim->param.x_max; // wrap around top
        }
    }

    cInt enz = node->enz; // parent phenotype
    if ( transformUnif(sim->state,0,1) < sim->param.lam_l )
        // if plasmid is lost at replication
    {
        enz = 0; // lose it
    }

    createNode(pos,enz,sim,err); // create node
}
