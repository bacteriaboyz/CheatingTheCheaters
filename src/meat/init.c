#include <stdio.h>
#include <math.h>
#include <string.h>

#include "init.h"

void initSim(simBac *sim, char *param_file, errorCode *err)
{
    // Get parameters:
    
    FILE *file;
    file = fopen("test.txt", "r");
    cInt max_line_length = 80;
    char sep = '='; // separates parameter name and value in input file
    char line[max_line_length];

    if (!file)
    {
        *err = FILE_NOT_FOUND;
        return;
    }

    cInt num_doses = 0; // Used to store the number of doses, alloc arr sizes

    while (fgets(line, sizeof(line), file)) // for every line of parameter file
    {
        char *tok = strtok(line,&sep); // initialize strtok iterator
        char *param = tok; // saves first token as parameter name
        tok = strtok(NULL,&sep); // get next token
        char *valStr = tok; // save token as value string
        double val; // will save numerical value, if any
 
        if (strcmp(param,"rng_phrase")) // if rng seed phrase
        {
            sim->param.rng_phrase = valStr; // no need to parse as double
        } 
        else if (strcmp(param,"doses_t")) // if dose array,
        {
            if (num_doses) // if dose arrays have been initialized,
            {
                char sep2 = ','; // separates values of dose times
                char *tok2 = strtok(valStr,&sep2); // get first dose time
                cFloat doses_t[num_doses]; // init array of dosage times
                sim->param.doses_t = doses_t; // assign pointer in param
                for (cInt i=0; i<num_doses; i++) // for every dose,
                {
                    cFloat d; // store float value of dose
                    sscanf(tok2,"%lf",&d); // parse as float
                    sim->param.doses_t[i] = d; // record the dose
                    tok2 = strtok(NULL,&sep2); // advance token
                }
            }
            else // if dose arrays not initialized,
            {
                *err = NUM_DOSES; // tantrum
            }
        }
        else if (strcmp(param,"doses_c")) // same as above, now concentrations
        {
            if (num_doses)
            {
                char sep2 = ',';
                char *tok2 = strtok(valStr,&sep2);
                cFloat doses_c[num_doses]; 
                sim->param.doses_c = doses_c;
                for (cInt i=0; i<num_doses; i++)
                {
                    cFloat d;
                    sscanf(tok2,"%lf",&d);
                    sim->param.doses_c[i] = d;
                    tok2 = strtok(NULL,&sep2);
                }
            }
            else
            {
                *err = NUM_DOSES;
            }
        }
        else // if value is scalar
        {
            sscanf(valStr,"%lf",&val);

            if (strcmp(param,"num_doses")) // if specifying number of doses,
            {
                num_doses = val; // assign value to number of doses
            }
            else if (strcmp(param,"z_max"))
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
                *err = UNKNOWN_PARAM;
                return;
            }
        }
        
        tok = strtok(NULL,&sep);
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
   
    // Initialize sim struct:

    //TODO: init buckets?

    // Init graph struct:
    stackInit(&sim->graph.rep_stack,LIMITS_MAX_BACT,err);
    stackInit(&sim->graph.die_stack,LIMITS_MAX_BACT,err);
    stackInit(&sim->graph.hgt_stack,LIMITS_MAX_BACT,err);
    stackInit(&sim->graph.dead_stack,LIMITS_MAX_BACT,err);
    setInit(&sim->graph.update_set,LIMITS_MAX_BACT,err);

    for (cInt i=0; i<LIMITS_MAX_BACT; i++) // set every node as unused, add them all to dead stack
    {
        sim->graph.bacteria[i].used = 0;
        stackPush(&sim->graph.dead_stack,&sim->graph.bacteria[i],err);
    }

    rngInitState(sim->state,sim->param.rng_phrase); //TODO init rng?
    sim->t = 0; // init time var
    sim->t_last_snap = 0; // init snapshot timer
    updateAB(sim); // init blood antibiotic
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
        for (cInt j=0; j<LIMITS_DIM-1; ++j)
        {
            pos[j] = transformUnif(sim->state,0,sim->param.x_max);
        }
        pos[LIMITS_DIM-1] = transformUnif(sim->state,0,z_max_i);

        createNode(pos,isProducer,sim,err);
        if (err != SUCCESS)
        {
            return;
        }
    }
    
    *err = SUCCESS;
}
