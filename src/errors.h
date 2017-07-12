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
    REJECT
} errorCode;

/*
 * Translates an error code to a human-readable message.
 */

const char *errorMsg(errorCode code);

#endif
