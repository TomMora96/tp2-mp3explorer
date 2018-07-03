/* errors.c */

#include <stdio.h>

#include "types.h"
#include "errors.h"

char *errors[MAX_ERRORS] = {
	MSG_OK,
	MSG_ERROR_NULL_POINTER,
	MSG_ERROR_PROGRAM_INVOCATION,
	MSG_ERROR_OUT_OF_MEMORY,
	MSG_ERROR_INVALID_INPUT_POSITION,
	MSG_ERROR_INPUT_FILE_NOT_FOUND,
	MSG_ERROR_XML_EXPORTER_NOT_SETTED,
	MSG_ERROR_CSV_EXPORTER_NOT_SETTED,
	MSG_ERROR_COMPARATOR_NOT_SETTED,
	MSG_ERROR_INVALID_TRACK_PARAMETER,
	MSG_ERROR_CLOSE_FILE
};

status_t print_errors (status_t status)
{
	fprintf(stderr, "%s\n", errors[status]);

	return OK;
}
