#include "abLocal.h"

cFloat abConc(cFloat d, simBac *sim)
{
    cFloat c; // stores concentration of antibiotic at this point
    if (d < sim->param.r_c) // if distance is less than one cell radius
    {
        if (sim->param.c_c < sim->c_b)
        {
            c = sim->param.c_c; // default lowest value
        }
        else // if bath is lower, use bath
        {
            c = sim->c_b;
        }
    }
    else // if further away,
    {
        c = ( sim->param.c_c + ( sim->c_b - sim->param.c_c ) * \
            ( 1.0 - ( sim->param.r_c / d ) ) );
            // See derivation in document
    }

    return c;
}
