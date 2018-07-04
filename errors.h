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
#define MSG_ERROR_XML_EXPORTER_NOT_SET "Tried to export vector to XML without setting the correct exporter function."
#define MSG_ERROR_CSV_EXPORTER_NOT_SET "Tried to export vector to CSV without setting the correct exporter function."
#define MSG_ERROR_COMPARATOR_NOT_SET "Tried to sort vector without setting a comparator function."
#define MSG_ERROR_INVALID_TRACK_PARAMETER "Tried to create new track from invalid parameters."
#define MSG_ERROR_CLOSE_FILE "File can not close."
#define MSG_ERROR_XML_HEADER_NOT_FOUND "Error open xml header."
#define MSG_ERROR_XML_FOOTER_NOT_FOUND "Error open xml footer."

status_t print_errors (status_t status);

#endif
