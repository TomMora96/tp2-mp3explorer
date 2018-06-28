/* errors.h */

#ifndef ERRORS__H
#define ERRORS__H

#define MSG_OK "OK"
#define MSG_ERROR_NULL_POINTER "Error null pointer."
#define MSG_ERROR_PROGRAM_INVOCATION "Error at program invocation."
#define MSG_ERROR_OUT_OF_MEMORY "Error out of memory."
#define MSG_ERROR_INVALID_INPUT_POSITION "Invalid input position."
#define MSG_ERROR_INPUT_FILE_NOT_FOUND "Cant open file."
#define MSG_ERROR_XML_EXPORTER_NOT_SETTED "Tried to export vector to XML without setting the correct exporter function."
#define MSG_ERROR_CSV_EXPORTER_NOT_SETTED "Tried to export vector to CSV without setting the correct exporter function."
#define MSG_ERROR_COMPARATOR_NOT_SETTED "Tried to sort vector without setting a comparator function."
#define MSG_ERROR_INVALID_TRACK_PARAMETER "Tried to create new track from invalid parameters."

status_t errors_printer (status_t status);

#endif
