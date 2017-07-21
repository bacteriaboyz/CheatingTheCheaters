#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "abBlood.h"
#include "create.h"
#include "update.h"
#include "snapshot.h"
#include "limits.h"
#include "transform.h"
#include "init.h"
#include "jsmn.h"
#include "limits.h"

#define INIT_EQ(x, y) (strcmp((x), (y)) == 0)

#define INIT_NUM_PARAMS 23

static void initReadParams(
                            simBac *sim,
                            char *buffer,
                            jsmntok_t *tokens,
                            int num_tokens,
                            errorCode *err
                          )
{
    bool initialized[INIT_NUM_PARAMS] = { false };

    for (int i = 0; i < num_tokens - 1; ++i)
    {
        jsmntok_t *tok = tokens + i;

        if (tok->type == JSMN_PRIMITIVE)
        {
            buffer[tok->end] = '\0';

            char *key = buffer + tok->start;

            tok = tokens + (++i);

            if (INIT_EQ(key, "name_run"))
            {
                buffer[tok->end] = '\0';

                strncpy(
                        sim->param.name_run,
                        buffer + tok->start,
                        LIMITS_MAX_LINE_LEN - 1
                       );

                initialized[0] = true;
            }
            else if (INIT_EQ(key, "doses_t"))
            {
                if (initialized[1] && tok->size != sim->param.num_doses)
                {
                    *err = MALFORMED_FILE;
                    return;
                }
                else if (!initialized[1])
                {
                    cInt num_doses = tok->size;
                    sim->param.num_doses = num_doses;
                    if (!(sim->param.doses_t = malloc(
                                                        num_doses *
                                                        sizeof(cFloat)
                                                      )))
                    {
                        *err = MEM;
                        return;
                    }

                    if (!(sim->param.doses_c = malloc(
                                                        num_doses *
                                                        sizeof(cFloat)
                                                      )))
                    {
                        *err = MEM;
                        free(sim->param.doses_t);
                        return;
                    }

                    initialized[1] = true;
                }

                tok = tokens + (++i);

                for (cInt j = 0; j < sim->param.num_doses; ++j)
                {
                    if (sscanf(
                                buffer + (tok + j)->start,
                                "%lf",
                                sim->param.doses_t + j
                              ) == 0)
                    {
                        *err = MALFORMED_FILE;
                        return;
                    }
                }

                i += sim->param.num_doses - 1;

                initialized[21] = true;
            }
            else if (INIT_EQ(key, "doses_c"))
            {
                if (initialized[1] && tok->size != sim->param.num_doses)
                {
                    *err = MALFORMED_FILE;
                    return;
                }
                else if (!initialized[1])
                {
                    cInt num_doses = tok->size;
                    sim->param.num_doses = num_doses;
                    if (!(sim->param.doses_t = malloc(
                                                        num_doses *
                                                        sizeof(cFloat)
                                                      )))
                    {
                        *err = MEM;
                        return;
                    }

                    if (!(sim->param.doses_c = malloc(
                                                        num_doses *
                                                        sizeof(cFloat)
                                                      )))
                    {
                        *err = MEM;
                        free(sim->param.doses_t);
                        return;
                    }

                    initialized[1] = true;
                }

                tok = tokens + (++i);

                for (cInt j = 0; j < sim->param.num_doses; ++j)
                {
                    if (sscanf(
                                buffer + (tok + j)->start,
                                "%lf",
                                sim->param.doses_c + j
                              ) == 0)
                    {
                        *err = MALFORMED_FILE;
                        return;
                    }
                }

                i += sim->param.num_doses - 1;

                initialized[22] = true;
            }
            else if (INIT_EQ(key, "z_max"))
            {
                if (sscanf(
                            buffer + tok->start,
                            "%lf",
                            &sim->param.z_max
                          ) == 0)
                {
                    *err = MALFORMED_FILE;
                    return;
                }

                initialized[2] = true;
            }
            else if (INIT_EQ(key, "d_bac"))
            {
                if (sscanf(
                            buffer + tok->start,
                            "%lf",
                            &sim->param.d_bac
                          ) == 0)
                {
                    *err = MALFORMED_FILE;
                    return;
                }

                initialized[3] = true;
            }
            else if (INIT_EQ(key, "gam_n"))
            {
                if (sscanf(
                            buffer + tok->start,
                            "%lf",
                            &sim->param.gam_n
                          ) == 0)
                {
                    *err = MALFORMED_FILE;
                    return;
                }

                initialized[4] = true;
            }
            else if (INIT_EQ(key, "lam_l"))
            {
                if (sscanf(
                            buffer + tok->start,
                            "%lf",
                            &sim->param.lam_l
                          ) == 0)
                {
                    *err = MALFORMED_FILE;
                    return;
                }

                initialized[5] = true;
            }
            else if (INIT_EQ(key, "lam_t"))
            {
                if (sscanf(
                            buffer + tok->start,
                            "%lf",
                            &sim->param.lam_t
                          ) == 0)
                {
                    *err = MALFORMED_FILE;
                    return;
                }

                initialized[6] = true;
            }
            else if (INIT_EQ(key, "bet_c"))
            {
                if (sscanf(
                            buffer + tok->start,
                            "%lf",
                            &sim->param.bet_c
                          ) == 0)
                {
                    *err = MALFORMED_FILE;
                    return;
                }

                initialized[7] = true;
            }
            else if (INIT_EQ(key, "r_c"))
            {
                if (sscanf(
                            buffer + tok->start,
                            "%lf",
                            &sim->param.r_c
                          ) == 0)
                {
                    *err = MALFORMED_FILE;
                    return;
                }

                initialized[8] = true;
            }
            else if (INIT_EQ(key, "alp_n"))
            {
                if (sscanf(
                            buffer + tok->start,
                            "%lf",
                            &sim->param.alp_n
                          ) == 0)
                {
                    *err = MALFORMED_FILE;
                    return;
                }

                initialized[9] = true;
            }
            else if (INIT_EQ(key, "x_base_factor"))
            {
                if (sscanf(
                            buffer + tok->start,
                            "%lf",
                            &sim->param.x_base_factor
                          ) == 0)
                {
                    *err = MALFORMED_FILE;
                    return;
                }

                initialized[10] = true;
            }
            else if (INIT_EQ(key, "x_max"))
            {
                if (sscanf(
                            buffer + tok->start,
                            "%lf",
                            &sim->param.x_max
                          ) == 0)
                {
                    *err = MALFORMED_FILE;
                    return;
                }

                initialized[10] = true;
            }
            else if (INIT_EQ(key, "t_s"))
            {
                if (sscanf(
                            buffer + tok->start,
                            "%lf",
                            &sim->param.t_s
                          ) == 0)
                {
                    *err = MALFORMED_FILE;
                    return;
                }

                initialized[11] = true;
            }
            else if (INIT_EQ(key, "t_max"))
            {
                if (sscanf(
                            buffer + tok->start,
                            "%lf",
                            &sim->param.t_max
                          ) == 0)
                {
                    *err = MALFORMED_FILE;
                    return;
                }

                initialized[12] = true;
            }
            else if (INIT_EQ(key, "t_b"))
            {
                if (sscanf(
                            buffer + tok->start,
                            "%lf",
                            &sim->param.t_b
                          ) == 0)
                {
                    *err = MALFORMED_FILE;
                    return;
                }

                initialized[13] = true;
            }
            else if (INIT_EQ(key, "v_w"))
            {
                if (sscanf(
                            buffer + tok->start,
                            "%lf",
                            &sim->param.v_w
                          ) == 0)
                {
                    *err = MALFORMED_FILE;
                    return;
                }

                initialized[13] = true;
            }
            else if (INIT_EQ(key, "k_a"))
            {
                if (sscanf(
                            buffer + tok->start,
                            "%lf",
                            &sim->param.k_a
                          ) == 0)
                {
                    *err = MALFORMED_FILE;
                    return;
                }

                initialized[14] = true;
            }
            else if (INIT_EQ(key, "c_i"))
            {
                if (sscanf(
                            buffer + tok->start,
                            "%lf",
                            &sim->param.c_i
                          ) == 0)
                {
                    *err = MALFORMED_FILE;
                    return;
                }

                initialized[15] = true;
            }
            else if (INIT_EQ(key, "h_i"))
            {
                if (sscanf(
                            buffer + tok->start,
                            "%lf",
                            &sim->param.h_i
                          ) == 0)
                {
                    *err = MALFORMED_FILE;
                    return;
                }

                initialized[16] = true;
            }
            else if (INIT_EQ(key, "phi_i"))
            {
                if (sscanf(
                            buffer + tok->start,
                            "%lf",
                            &sim->param.phi_i
                          ) == 0)
                {
                    *err = MALFORMED_FILE;
                    return;
                }

                initialized[16] = true;
            }
            else if (INIT_EQ(key, "c_m"))
            {
                if (sscanf(
                            buffer + tok->start,
                            "%lf",
                            &sim->param.c_m
                          ) == 0)
                {
                    *err = MALFORMED_FILE;
                    return;
                }

                initialized[17] = true;
            }
            else if (INIT_EQ(key, "c_c"))
            {
                if (sscanf(
                            buffer + tok->start,
                            "%lf",
                            &sim->param.c_c
                          ) == 0)
                {
                    *err = MALFORMED_FILE;
                    return;
                }

                initialized[18] = true;
            }
            else if (INIT_EQ(key, "f_e"))
            {
                if (sscanf(
                            buffer + tok->start,
                            "%lf",
                            &sim->param.f_e
                          ) == 0)
                {
                    *err = MALFORMED_FILE;
                    return;
                }

                initialized[19] = true;
            }
            else if (INIT_EQ(key, "snap_freq"))
            {
                if (sscanf(
                            buffer + tok->start,
                            "%lf",
                            &sim->param.snap_freq
                          ) == 0)
                {
                    *err = MALFORMED_FILE;
                    return;
                }

                initialized[20] = true;
            }
        }
    }

    for (cInt i = 0; i < INIT_NUM_PARAMS; ++i)
    {
        if (!initialized[i])
        {
            *err = MALFORMED_FILE;
            return;
        }
    }

    *err = SUCCESS;
}

static void initReadFile(simBac *sim, char *param_file, errorCode *err)
{
    FILE *file;
    char *buffer;
    jsmntok_t *tokens;
    size_t len;
    jsmn_parser parser;
    int num_tokens;

    // Read the param file into memory.

    if (!(file = fopen(param_file, "r")))
    {
        *err = FILE_NOT_FOUND;
        return;
    }

    if (!(buffer = calloc(LIMITS_MAX_FILE_SIZE, 1)))
    {
        *err = MEM;
        fclose(file);
        return;
    }

    len = fread(buffer, 1, LIMITS_MAX_FILE_SIZE, file);

    if (ferror(file))
    {
        *err = ERR_READ_FILE;
        fclose(file);
        free(buffer);
        return;
    }

    fclose(file);

    // Parse the param file.

    jsmn_init(&parser);

    if ((num_tokens = jsmn_parse(
                                    &parser,
                                    buffer,
                                    len,
                                    NULL,
                                    0
                                 )) < 0)
    {
        *err = MALFORMED_FILE;
        free(buffer);
        return;
    }

    if (!(tokens = malloc(num_tokens * sizeof(jsmntok_t))))
    {
        *err = MEM;
        free(buffer);
        return;
    }

    jsmn_init(&parser);

    jsmn_parse(&parser, buffer, len, tokens, num_tokens);

    initReadParams(sim, buffer, tokens, num_tokens, err);

    free(buffer);
    free(tokens);
}



void initSim(simBac *sim, char *param_file, bool output, errorCode *err)
{
    initReadFile(sim, param_file, err);

    if (*err != SUCCESS)
    {
        return;
    }

    sim->param.output = output; // handle whether or not output frame info

    // Calculate remaining parameters:

    sim->param.x_max = sim->param.x_base_factor * sim->param.x_max;
        // larger base

    sim->param.v_t = pow( sim->param.x_max, LIMITS_DIM ) * sim->param.z_max;
    sim->param.n_max = sim->param.v_t / \
        ( 4.0 * sqrt(2.0) * pow( sim->param.d_bac, 3.0 ) );
        // 3D sphere packing formula for bacterial density
        // ONLY VALID FOR 3D
        // other D's are left as exercise for the reader :P
    sim->param.rho_b = 1.0 / ( 4.0 * sqrt( 2.0 ) * pow( sim->param.r_c, 3.0 ) );
        // using sphere packing density
    sim->param.r_d = sim->param.r_c / ( 1.0 - sim->param.bet_c );
        // see document for derivation
    sim->param.v_n = 4.0 * M_PI * pow( sim->param.r_d, 3.0 ) / 3.0;
    sim->param.n_n_max = sim->param.rho_b * sim->param.v_n;
    sim->param.gam_ab = sim->param.t_s * sim->param.k_a / sim->param.v_w;
        // renal clearance in time step
    sim->param.c_h = sim->param.c_m;
        // midpoint, MIC
    sim->param.h = log( 3.0 ) / \
        ( log( ( sim->param.c_h / sim->param.c_i ) ) );
        // Hill coefficient expressed in terms of 1/3 and 2/3 total height pts. 

    if (sim->param.output)
    {
        FILE *ts_f; // time series file pointer

        char ts_file_name[LIMITS_MAX_LINE_LEN+17];

        sprintf(ts_file_name, \
            "time_series_%s.csv",sim->param.name_run);
            // prints time series file name to variable

        ts_f = fopen(ts_file_name,"w"); // open csv file
        if (!ts_f)
        {
            *err = ERR_CREATE_FILE;
            fclose(ts_f);
            return;
        }
        int pChk = fprintf(ts_f,"Time,Num_Bac,Num_Prod,AB_Conc\n"); 
            // print csv file header
        if (pChk < 0)
        {
            *err = PRINT_FAIL;
            fclose(ts_f);
            return;
        }
        sim->t_series_file = ts_f; // save time series file
    }

    updateAB(sim); // init blood antibiotic

    cVec b_dims; // will store bucket dimensions
    cInt num_b[LIMITS_DIM]; // contain number of buckets in each dim
    for (cInt i=0; i<LIMITS_DIM-1; ++i)
    {
        num_b[i] = floor( sim->param.x_max / sim->param.r_d ); // num buckets
        if (num_b[i] < 1) // if under 1, reset to 1
        {
            num_b[i] = 1;
        }
        b_dims[i] = sim->param.x_max / num_b[i]; // set this bucket dimension
    }

    num_b[LIMITS_DIM-1] = floor( sim->param.z_max / sim->param.r_d );
        // num buckets on z axis
    if (num_b[LIMITS_DIM-1] < 1) // if under 0, reset to 0
    {
        num_b[LIMITS_DIM-1] = 1;
    }

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
    cFloat x_min_sow = sim->param.x_max / 2.0 - \
        sim->param.x_max / ( sim->param.x_base_factor * 2.0 );
        // min value of initial seed
    cFloat x_max_sow = sim->param.x_max / 2.0 + \
        sim->param.x_max / ( sim->param.x_base_factor * 2.0 );
        // min value of initial seed

    bool conn; // connection check var

    for (cInt i=0; i < LIMITS_MAX_TRIES; ++i)
        // try until connected or tired
    {
        for (cInt i=0; i<LIMITS_MAX_BACT; ++i)
            // set every node as unused, add them all to dead stack
        {
            sim->graph.bacteria[i].used = 0;
            stackPush(&sim->graph.dead_stack,&sim->graph.bacteria[i],err);
        }

        for (cInt i=0; i<num_cells_i; ++i) // for every cell that will be created,
        {
            cInt isProducer = 0; // default not producer
            if (transformUnif(sim->state,0,1) < sim->param.phi_i)
                // random distribute producers according to initial proportion
            {
                isProducer = 1;
            }

            cVec pos;
            for (cInt j=0; j<LIMITS_DIM-1; ++j) // assign all dims except last
            {
                pos[j] = transformUnif(sim->state,x_min_sow,x_max_sow);
            }
            pos[LIMITS_DIM-1] = transformUnif(sim->state,0,z_max_i); // do last

            createNode(pos,isProducer,sim,err); // create bacteria
            if (*err != SUCCESS)
            {
                return;
            }
        }
        // the last bacteria should be used if connectChkGraph is to work
        if (!sim->graph.bacteria[LIMITS_MAX_BACT-1].used)
        {
            *err = NO_INIT_BACT;
            return;
        }

        conn = connectChkGraph(sim,err); // check connection
        if (*err != SUCCESS)
        {
            return;
        }

        if (conn) // Checks for one continuous clump of cells
        {
            break;
        }

        sim->num_bac = 0; // reset counters
        sim->num_pro = 0;
        stackReset(&sim->graph.dead_stack); // reset the stack
        nnFree(&sim->buckets); // free buckets
        nnInit(&sim->buckets,b_dims,num_b,err); // initialize nearest neighbor ds
        if (*err != SUCCESS)
        {
            return;
        }
    }

    *err = conn ? SUCCESS : REJECT;
}
