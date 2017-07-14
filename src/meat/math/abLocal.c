#include "abLocal.h"

cFloat abConc(cFloat d, simBac *sim)
{
    return ( sim->param.c_c + ( sim->c_b - sim->param.c_c ) * \
        ( 1.0 - ( sim->param.r_c / d ) ) );
        // See derivation in document
}
