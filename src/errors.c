#include "errors.h"

const char *errorMsg(errorCode code)
{
    switch (code)
    {
        case MEM:
            return "Memory allocation error."
        default:
            return "No error."
    }
}
