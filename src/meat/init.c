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

    cInt num_doses = 0;
    
    while (fgets(line, sizeof(line), file))
    {
        char *tok = strtok(line,sep);
        char *param = tok;
        strtok(NULL,sep);
        char *valStr = tok;
        double val;
 
        if (strcmp(param,"num_doses"))
        {
            sscanf(valStr,"%lf",&num_doses);
            cFloat[num_doses] doses_c;
            sim->param.doses_c = &doses_c;
            cFloat[num_doses] doses_t;
            sim->param.doses_t = &doses_t;
        }
        else if (strcmp(param,"doses_t"))
        {
            if (num_doses)
            {
                ichar sep2 = ',';
                char *tok2 = strtok(valStr,sep2);
                for (cInt i=0; i<num_doses; i++)
                {
                    sim->param.doses_t[i] = tok2;
                    tok2 = strtok(NULL,sep2);
                }
                sim->param.doses_t = val;
            }
            else
            {
                err = NUM_DOSES;
            }
        }
        else if (strcmp(param,"doses_c"))
        {
            if (num_doses)
            {
                ichar sep2 = ',';
                char *tok2 = strtok(valStr,sep2);
                for (cInt i=0; i<num_doses; i++)
                {
                    sim->param.doses_c[i] = tok2;
                    tok2 = strtok(NULL,sep2);
                }
                sim->param.doses_t = val;
            }
            else
            {
                err = NUM_DOSES;
            }
        }
        else
        {
            sscanf(valStr,"%lf",&val);

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
            else if (strcmp(param,"h_i"))
            {
                sim->param.h_i = val;
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
                err = UNKNOWN_PARAM;
                return;
            }
        }
        
        tok = strtok(NULL,sep);
    }

    fclose(file);

    // Calculate remaining parameters:

    sim->param.v_t = pow( sim->param.x_max, 2.0 ) * sim->param.z_max;
    sim->param.n_max = sim->param.v_t / \
        ( 4.0 * sqrt(2.0) * pow( sim->param.d_bac, 3.0 ) );
        // 3D sphere packing formula for bacterial density
        // ONLY VALID FOR 3D
        // other D's are left as exercise for the reader :P
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
   
    // Initialize sim struct

    //TODO: init buckets?
    sim->graph; //TODO? init all stacks and set
    for () //TODO: init every node as unused, add them all to dead stack

    sim->state; //TODO? init rng?
    sim->t = 0; // init time var
    sim->t_last_snap = 0; // init snapshot timer
    sim->c_b = updateAB(sim) // init blood antibiotic
    sim->dose_num = 0; // init dose number counter
    sim->num_bac = 0;
    sim->num_pro = 0;

    // Sow initial cells
    
    cFloat num_cells_i = sim->param.n_max * sim->param.h_i;
    cFloat z_max_i = sim->param.z_max * sim->param.h_i;
    for (cInt i=0; i<num_cells_i; i++)
    {
        ++sim->num_bac; // advance bacteria counter

        cInt isProducer = 0;
        if (transformUnif(sim->state,0,1) < sim->param.phi_i)
        {
            isProducer = 1;
            ++sim->num_pro; // advance producer bacteria counter
        }
        
        cVec pos;
        for (cInt j=0; i<LIMITS_DIM-1; i++)
        {
            pos[i] = transformUnif(sim->state,0,sim->param.x_max);
        }
        pos[LIMITS_DIM-1] = transformUnif(sim->state,0,z_max_i);

        createNode(pos,isProducer,sim,err);
    }
}
