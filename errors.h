/* errors.h */

#ifndef ERRORS__H
#define ERRORS__H

#define MAX_ERRORS 13

#define MSG_OK "OK"
#define MSG_ERROR_NULL_POINTER "Error null pointer."
#define MSG_ERROR_PROGRAM_INVOCATION "Error at program invocation."
#define MSG_ERROR_OUT_OF_MEMORY "Error out of memory."
#define MSG_ERROR_INVALID_INPUT_POSITION "Invalid input position."
#define MSG_ERROR_INPUT_FILE_NOT_FOUND "Cant open file."
#define MSG_ERROR_EXPORTER_NOT_SET "Tried to export vector without setting an exporter function."
#define MSG_ERROR_COMPARATOR_NOT_SET "Tried to sort vector without setting a comparator function."
#define MSG_ERROR_INVALID_TRACK_PARAMETER "Tried to create new track from invalid parameters."
#define MSG_ERROR_OUT_OF_DISK_SPACE "Out of disk space."
#define MSG_ERROR_HEADER_FILE_NOT_FOUND "Error open header file."
#define MSG_ERROR_FOOTER_FILE_NOT_FOUND "Error open footer file."

status_t print_errors (status_t status);

#endif
