#include "errors.h"

const char *errorMsg(errorCode code)
{
    switch (code)
    {
        case SUCCESS:
            return "No error.";
        case MEM:
            return "Memory allocation error.";
        case REJECT:
            return "Rejection sampling threshold reached.";
        case NOT_FOUND:
            return "Object not found in hash table.";
        case INCONSISTENT:
            return "Program in inconsistent state.";
        case FILE_NOT_FOUND:
            return "Input parameter file with the given address not found.";
        case MALFORMED_FILE:
            return "Could not understand parameter file.";
        case NUM_DOSES:
            return "The dosage time array or dosage concentration array was "
                "passed before the number of doses in the parameter input "
                "file.";
        case ERR_CREATE_FILE:
            return "There was a problem creating a file (csv or vtk output "
                "files).";
        case ERR_READ_FILE:
            return "Could not read file.";
        case PRINT_FAIL:
            return "Could not print to file correctly (csv or vtk files).";
        case OUT_OF_BACT:
            return "The maximum number of bacteria set as a limit was "
                "surpassed.";
        case NO_INIT_BACT:
            return "No used bacteria found in last position of bacteria array";
    }

    return "This should never happen.";
}
