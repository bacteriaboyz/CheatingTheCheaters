#include <stdio.h>
#include <math.h>

#include "init.h"

void initSim(simBac *sim, char *param_file, errorCode *err)
{
    // Get parameters:
    FILE *file;
    file = fopen("test.txt", "r");
    cInt max_line_length = 80;
    char sep = '=';
    char line[max_line_length];
    cInt line_num = 0;

    if (!file)
    {
        err = FILE_NOT_FOUND;
        return;
    }

    while (fgets(line, sizeof(line), file))
    {
        char *tok = strtok(line,sep);
        char *param = tok;
        char *valStr = tok;
        double val;
 
        if (strcmp(param,"doses_t"))
        {
            char sep2 = ',';
            char *tok2 = strtok(valStr,sep2);
            while (tok2)
            {
                
                tok2 = strtok(NULL,sep2);
            } //TODO: finish parsing dosage arrays
            sim->param.doses_t = val;
        }
        else if (strcmp(param,"doses_c"))
        {
            sim->param.phi_i = val;
        }
        else
        {
            sscanf(tok,"%lf",&val);

            if (strcmp(param,"z_max"))
            {
                sim->param.z_max = val;
            }
            else if (strcmp(param,"d_bac"))
            {
                sim->param.d_bac = val;
            }
            else if (strcmp(param,"gam_n"))
            {
                sim->param.gam_n = val;
            }
            else if (strcmp(param,"lam_l"))
            {
                sim->param.lam_l = val;
            }
            else if (strcmp(param,"lam_t"))
            {
                sim->param.lam_t = val;
            }
            else if (strcmp(param,"bet_c"))
            {
                sim->param.bet_c = val;
            }
            else if (strcmp(param,"r_c"))
            {
                sim->param.r_c = val;
            }
            else if (strcmp(param,"alp_n"))
            {
                sim->param.alp_n = val;
            }
            else if (strcmp(param,"x_max"))
            {
                sim->param.x_max = val;
            }
            else if (strcmp(param,"t_s"))
            {
                sim->param.t_s = val;
            }
            else if (strcmp(param,"t_max"))
            {
                sim->param.t_max = val;
            }
            else if (strcmp(param,"v_w"))
            {
                sim->param.v_w = val;
            }
            else if (strcmp(param,"k_a"))
            {
                sim->param.k_a = val;
            }
            else if (strcmp(param,"c_i"))
            {
                sim->param.c_i = val;
            }
            else if (strcmp(param,"z_i"))
            {
                sim->param.z_i = val;
            }
            else if (strcmp(param,"phi_i"))
            {
                sim->param.phi_i = val;
            }
            else if (strcmp(param,"c_m"))
            {
                sim->param.c_m = val;
            }
            else if (strcmp(param,"c_c"))
            {
                sim->param.c_c = val;
            }
            else if (strcmp(param,"f_e"))
            {
                sim->param.f_e = val;
            }
            else
            {
                err = UNKNOWN_PARAMETER;
                return;
            }
        }
        
        tok = strtok(NULL,sep);
    }

    fclose(file);
    // TODO: read param_file

    // Calculate remaining parameters:
    sim->param.v_t = pow( sim->param.x_max, 2.0 ) * sim->param.z_max;
    sim->param.n_max = sim->param.v_t / \
        ( 4.0 * sqrt(2.0) * pow( sim->param.d_bac, 3.0 ) );
        // 3D sphere packing formula for bacterial density
    sim->param.rho_b = sim->param.n_n_max / sim->param.v_t;
    sim->param.r_d = sim->param.r_c / ( 1.0 - sim->param.bet_c );
        // see document for derivation
    sim->param.v_n = 4.0 * M_PI * pow( sim->param.r_d, 3.0 ) / 3.0;
    sim->param.n_n_max = sim->param.rho_b * sim->param.v_n;
    sim->param.gam_ab = sim->param.t_s * sim->param.k_a / sim->param.v_w;
        // renal clearance in time step
    sim->param.c_h = ( sim->param.c_i + sim->param.c_m ) / 2.0;
        // midpoint, hill function is symmetrical around midoint
    sim->param.h = log( 2.0 ) / \
        ( log( 1.0 + ( sim->param.c_m / sim->param.c_i ) ) - log( 2.0 ) );
        // Hill coefficient expressed in terms of 1/3 and 2/3 total height pts.
    
    // Sow initial cells
    
}
