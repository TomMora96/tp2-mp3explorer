/* errors.h */

#ifndef ERRORS__H
#define ERRORS__H

#define MSG_OK "OK"
#define MSG_ERROR_NULL_POINTER "Error null pointer."
#define MSG_ERROR_PROGRAM_INVOCATION "Error at program invocation."
#define MSG_ERROR_OUT_OF_MEMORY "Error out of memory"

status_t errors_printer (status_t status);

#endif
