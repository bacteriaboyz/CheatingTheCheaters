#ifndef _ERRORS_H
#define _ERRORS_H

/*
 * Every function with the potential for error should take an argument of type
 * errorCode* and set it either to SUCCESS or an error code.
 */

typedef enum
{
    SUCCESS,
    MEM,
    REJECT,
    NOT_FOUND,
    INCONSISTENT,
    FILE_NOT_FOUND,
    MALFORMED_FILE,
    NUM_DOSES,
    ERR_CREATE_FILE,
    ERR_READ_FILE,
    PRINT_FAIL,
    OUT_OF_BACT,
    NO_INIT_BACT
} errorCode;

/*
 * Translates an error code to a human-readable message.
 */

const char *errorMsg(errorCode code);

#endif
