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
        case UNKNOWN_PARAM:
            return "A parameter was given with a field name that is not \
                recognized by the input file parser.";
        case NUM_DOSES:
            return "The dosage time array or dosage concentration array was \
                passed \nbefore the number of doses in the parameter input \
                file.";
        case ERROR_CREATE_FILE:
            return "There was a problem creating a file (csv or vtk output \
                files";
        case PRINT_FAIL:
            return "Could not print to file correctly (csv or vtk files).";
    }

    return "This should never happen.";
}
