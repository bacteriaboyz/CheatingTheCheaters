#include <stdio.h>
#include <math.h>
#include <string.h>

#include "init.h"
#include "limits.h"

#ifndef INIT_SEP1
#define INIT_SEP1 "="
#endif

#ifndef INIT_SEP2
#define INIT_SEP2 ","
#endif

void initSim(simBac *sim, char *param_file, errorCode *err)
{
    // Get parameters:

    FILE *file;
    file = fopen(param_file, "r");
    if (!file)
    {
        *err = FILE_NOT_FOUND;
        fclose(file);
        return;
    }
    char line[LIMITS_MAX_LINE_LEN];

    if (!file)
    {
        *err = FILE_NOT_FOUND;
        fclose(file);
        return;
    }

    cInt num_doses = 0; // Used to store the number of doses, alloc arr sizes

    while (fgets(line, sizeof(line), file)) // for every line of parameter file
    {
        char *tok = strtok(line,INIT_SEP1); // initialize strtok iterator
        char *param = tok; // saves first token as parameter name
        tok = strtok(NULL,INIT_SEP2); // get next token
        char *valStr = tok; // save token as value string
        double val; // will save numerical value, if any

        if (strcmp(param,"rng_phrase") == 0) // if rng seed phrase
        {
            sim->param.rng_phrase = valStr; // no need to parse as double
        }
        if (strcmp(param,"name_run") == 0) // if name of run
        {
            sim->param.name_run = valStr; // no need to parse as double
        }
        else if (strcmp(param,"doses_t") == 0) // if dose array,
        {
            if (num_doses) // if dose arrays have been initialized,
            {
                char *tok2 = strtok(valStr,INIT_SEP2); // get first dose time
                cFloat doses_t[num_doses]; // init array of dosage times
                sim->param.doses_t = doses_t; // assign pointer in param
                for (cInt i=0; i<num_doses; i++) // for every dose,
                {
                    cFloat d; // store float value of dose
                    sscanf(tok2,"%lf",&d); // parse as float
                    sim->param.doses_t[i] = d; // record the dose
                    tok2 = strtok(NULL,INIT_SEP2); // advance token
                }
            }
            else // if dose arrays not initialized,
            {
                *err = NUM_DOSES; // tantrum
                fclose(file);
                return;
            }
        }
        else if (strcmp(param,"doses_c") == 0) // same as above, now concentrations
        {
            if (num_doses)
            {
                char *tok2 = strtok(valStr, INIT_SEP2);
                cFloat doses_c[num_doses];
                sim->param.doses_c = doses_c;
                for (cInt i=0; i<num_doses; i++)
                {
                    cFloat d;
                    sscanf(tok2,"%lf",&d);
                    sim->param.doses_c[i] = d;
                    tok2 = strtok(NULL,INIT_SEP2);
                }
            }
            else
            {
                *err = NUM_DOSES;
                fclose(file);
                return;
            }
        }
        else // if value is scalar
        {
            sscanf(valStr,"%lf",&val);

            if (strcmp(param,"num_doses") == 0) // if specifying number of doses,
            {
                num_doses = val; // assign value to number of doses
            }
            else if (strcmp(param,"z_max") == 0)
            {
                sim->param.z_max = val;
            }
            else if (strcmp(param,"d_bac") == 0)
            {
                sim->param.d_bac = val;
            }
            else if (strcmp(param,"gam_n") == 0)
            {
                sim->param.gam_n = val;
            }
            else if (strcmp(param,"lam_l") == 0)
            {
                sim->param.lam_l = val;
            }
            else if (strcmp(param,"lam_t") == 0)
            {
                sim->param.lam_t = val;
            }
            else if (strcmp(param,"bet_c") == 0)
            {
                sim->param.bet_c = val;
            }
            else if (strcmp(param,"r_c") == 0)
            {
                sim->param.r_c = val;
            }
            else if (strcmp(param,"alp_n") == 0)
            {
                sim->param.alp_n = val;
            }
            else if (strcmp(param,"x_max") == 0)
            {
                sim->param.x_max = val;
            }
            else if (strcmp(param,"t_s") == 0)
            {
                sim->param.t_s = val;
            }
            else if (strcmp(param,"t_max") == 0)
            {
                sim->param.t_max = val;
            }
            else if (strcmp(param,"v_w") == 0)
            {
                sim->param.v_w = val;
            }
            else if (strcmp(param,"k_a") == 0)
            {
                sim->param.k_a = val;
            }
            else if (strcmp(param,"c_i") == 0)
            {
                sim->param.c_i = val;
            }
            else if (strcmp(param,"h_i") == 0)
            {
                sim->param.h_i = val;
            }
            else if (strcmp(param,"phi_i") == 0)
            {
                sim->param.phi_i = val;
            }
            else if (strcmp(param,"c_m") == 0)
            {
                sim->param.c_m = val;
            }
            else if (strcmp(param,"c_c") == 0)
            {
                sim->param.c_c = val;
            }
            else if (strcmp(param,"f_e") == 0)
            {
                sim->param.f_e = val;
            }
            else
            {
                *err = UNKNOWN_PARAM;
                fclose(file);
                return;
            }
        }

        tok = strtok(NULL,INIT_SEP1);
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

    for (cInt i=0; i<LIMITS_MAX_BACT; ++i)
        // set every node as unused, add them all to dead stack
    {
        // Memory should be zeroed out
        sim->graph.bacteria[i].used = 0;
        stackPush(&sim->graph.dead_stack,&sim->graph.bacteria[i],err);
    }

    FILE *ts_f; // time series file pointer
    char ts_file_name[80];
    sprintf(ts_file_name, \
        "time_series_%s.csv",sim->param.name_run);
        // prints time series file name to variable

    ts_f = fopen(ts_file_name,"w"); // open csv file
    if (!ts_f)
    {
        *err = ERROR_CREATE_FILE;
        fclose(ts_f);
        return;
    }
    cInt pChk = fprintf(ts_f,"Time,Num_Bac,Num_Prod,AB_Conc\n"); 
        // print csv file header
    if (pChk < 0)
    {
        *err = PRINT_FAIL;
        fclose(ts_f);
        return;
    }
    sim->t_series_file = ts_f; // save time series file

    updateAB(sim); // init blood antibiotic

    cVec b_dims; // will store bucket dimensions
    cInt num_b[LIMITS_DIM]; // contain number of buckets in each dim
    for (cInt i=0; i<LIMITS_DIM-1; ++i)
    {
        num_b[i] = floor( sim->param.x_max / sim->param.r_d ); // num buckets
        b_dims[i] = sim->param.x_max / num_b[i]; // set this bucket dimension
        if (num_b[i] < 1) // if under 1, reset to 1
        {
            num_b[i] = 1;
        }
    }

    num_b[LIMITS_DIM-1] = floor( sim->param.z_max / sim->param.r_d );
        // num buckets on z axis
    b_dims[LIMITS_DIM-1] = sim->param.z_max / num_b[LIMITS_DIM-1]; // set this bucket dim

    nnInit(&sim->buckets,b_dims,num_b,err); // initialize nearest neighbor ds
    if (*err != SUCCESS)
    {
        return;
    }

    // Sow initial cells

    cFloat num_cells_i = sim->param.n_max * sim->param.h_i;
        // initial number of cells
    cFloat z_max_i = sim->param.z_max * sim->param.h_i;
        // maximum z height of cells initially
    for (cInt i=0; i<num_cells_i; ++i) // for every cell that will be created,
    {
        ++sim->num_bac; // advance bacteria counter

        cInt isProducer = 0; // default not producer
        if (transformUnif(sim->state,0,1) < sim->param.phi_i)
            // random distribute producers according to initial proportion
        {
            isProducer = 1;
            ++sim->num_pro; // advance producer bacteria counter
        }

        cVec pos;
        for (cInt j=0; j<LIMITS_DIM-1; ++j) // assign all dims except last
        {
            pos[j] = transformUnif(sim->state,0,sim->param.x_max);
        }
        pos[LIMITS_DIM-1] = transformUnif(sim->state,0,z_max_i); // do last

        createNode(pos,isProducer,sim,err); // create bacteria
        if (*err != SUCCESS)
        {
            return;
        }
    }

    *err = SUCCESS;
}
