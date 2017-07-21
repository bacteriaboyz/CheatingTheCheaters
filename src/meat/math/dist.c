#include <math.h>

#include "dist.h"

cFloat distance(nodeBac *n1, nodeBac *n2, simBac *sim)
{
    cFloat sumSqrs = 0; // stores value of sum of squares for pythagorean law
    cInt i = 0; // counter for iterating through dimensions
    while (i < LIMITS_DIM-1)
        // for every distance in every axis other than the non-wrapping one
    {
        cFloat d =  fabs( n1->pos[i] - n2->pos[i] ); // regular distance  

#ifndef NO_WRAP
        if ( d > sim->param.x_max / 2.0 )
        // if the wrapped distance is shorter than the regular distance
        {
            d = sim->param.x_max - d; // use wraparound distance instead
        }
#endif
        sumSqrs += pow( d, 2.0 ); // square distance
        
        ++i; // advance counter
    }

    sumSqrs += pow( n1->pos[i] - n2->pos[i] , 2.0 );
        // no wraparound in final dimension
    
    return sqrt(sumSqrs); // sqrt to complete pythagorean law
}
