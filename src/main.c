#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "cleanup.h"
#include "errors.h"
#include "init.h"
#include "mainloop.h"
#include "setup.h"
#include "sim.h"

/* Original main function

int main(void)
{
    puts("Poop");

    return 0;
}

*/

// Crappy replacement main function

int main(int argc, char **argv)
{
    if ((argc != 4 && argc != 5) || (argc == 5 && strcmp(argv[4], "--quiet") != 0))
    {
        fprintf(stderr, "Usage: %s namerun filename seed [--quiet]\n", argv[0]);
        return EXIT_FAILURE;
    }

    simBac sim;

    errorCode error;

    setupSim(&sim, argv[3], &error);

    if (error != SUCCESS)
    {
        goto main_error;
    }

    initSim(&sim, argv[1], argv[2], argc == 4, &error);

    if (error != SUCCESS)
    {
        goto main_error;
    }

    mainloopSim(&sim, &error);

    if (error != SUCCESS)
    {
        goto main_error;
    }

    printf("%" TYPES_WRITE ",%" TYPES_WRITE ",%f\n", \
        sim.num_bac, sim.num_pro, sim.t);

    return EXIT_SUCCESS;

main_error:
    cleanupSim(&sim);
    fprintf(stderr, "Error: %s\n", errorMsg(error));
    return EXIT_FAILURE;
}
