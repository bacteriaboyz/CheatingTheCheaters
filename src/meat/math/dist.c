#include <math.h>

#include "dist.h"

cFloat distance(nodeBac *n1, nodeBac *n2)
{
    cFloat sumSqrs = 0;
    for (cInt i=0; i<LIMITS_DIM; i++)
    {
        sumSqrs += pow( ( n1->pos[i] - n2->pos[i] ), 2.0 );
    }
    
    return sqrt(sumSqrs);
}
