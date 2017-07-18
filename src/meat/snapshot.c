#include <stdio.h>
#include <math.h>

#include "snapshot.h"
#include "types.h"

void snapshotSim(simBac *sim, errorCode *err)
{
    //For the csv file
    cInt chk = fprintf(sim->t_series_file, "%.6e,%" TYPES_WRITE ",%" TYPES_WRITE ",%.6e\n", sim->t, sim->num_bac, sim->num_pro, sim->c_b);
    cInt r;
    cInt b;

    if(chk < 0)
    {
        *err = PRINT_FAIL;
        return;
    }


    //for the VTK file

    FILE *vtk_f;
    char vtk_file_name[LIMITS_MAX_LINE_LEN];
    snprintf(vtk_file_name, LIMITS_MAX_LINE_LEN, "pos_%s_%.4f.vtk", sim->param.name_run, floor(sim->t/sim->param.t_s));
    vtk_f = fopen(vtk_file_name, "w");

    if(!vtk_f)
    {
        *err = ERR_CREATE_FILE;
        return;
    }

    FILE *vtk_f2;
    char vtk_file_name2[LIMITS_MAX_LINE_LEN];
    snprintf(vtk_file_name2, LIMITS_MAX_LINE_LEN, "col_%s_%.4f.vtk", sim->param.name_run, floor(sim->t/sim->param.t_s));
    vtk_f2 = fopen(vtk_file_name2, "w");

    if(!vtk_f2)
    {
        *err = ERR_CREATE_FILE;
        goto ss_jmp2;
    }

    chk = fprintf(vtk_f, "# vtk DataFile Version 2.0\n \
    %s \nASCII \nDATASET POLYDATA \nPOINTS %" TYPES_WRITE " float \n", vtk_file_name, sim->num_bac);
    if(chk < 0)
    {
        *err = PRINT_FAIL;
        goto ss_jmp1;
    }
    chk = fprintf(vtk_f2, "POINT_DATA %" TYPES_WRITE " \n SCALARS scalars float 1\n \
    LOOKUP_TABLE_colors \n", sim->num_bac);
    if(chk < 0)
    {
        *err = PRINT_FAIL;
        goto ss_jmp1;
    }

    for (cInt i = 0; i < sim->num_bac; ++i)
    {
        chk = fprintf(vtk_f2, "%" TYPES_WRITE ".0\n", i);
        if(chk < 0)
        {
            *err = PRINT_FAIL;
            goto ss_jmp1;
        }
    }
    chk = fprintf(vtk_f2, "LOOKUP_TABLE_colors %" TYPES_WRITE "\n", sim->num_bac);
    for (cInt i = 0; i < LIMITS_MAX_BACT; ++i)
    {
        if (sim->graph.bacteria[i].used)
        {
            if(sim->graph.bacteria[i].enz == 1)
            {
                r = 1;
                b = 0;
            }
            else
            {
                r = 0;
                b = 1;
            }

            chk = fprintf(vtk_f, "%.6e %.6e %.6e\n", \
                sim->graph.bacteria[i].pos[0],sim->graph.bacteria[i].pos[1], \
                sim->graph.bacteria[i].pos[2]);

            if(chk < 0)
            {
                *err = PRINT_FAIL;
                goto ss_jmp1;
            }

            chk = fprintf(vtk_f2, "%" TYPES_WRITE " 0 %" TYPES_WRITE " 1\n", r, b);
            if(chk < 0)
            {
                *err = PRINT_FAIL;
                goto ss_jmp1;
            }
        }
    }

    *err = SUCCESS;

ss_jmp1:
    fclose(vtk_f2);
ss_jmp2:
    fclose(vtk_f);
}
