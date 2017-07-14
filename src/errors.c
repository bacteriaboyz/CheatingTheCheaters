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
    }

    return "This should never happen.";
}
