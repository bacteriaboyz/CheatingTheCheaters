#include "errors.h"

const char *errorMsg(errorCode code)
{
    switch (code)
    {
        case SUCCESS:
            return "No error.";
        case MEM:
            return "Memory allocation error.";
    }

    return "This should never happen.";
}
