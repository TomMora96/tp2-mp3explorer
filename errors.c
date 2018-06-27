/* errors.c */

#include <stdio.h>

#include "types.h"
#include "errors.h"

char *errors[] = {
	MSG_OK,
	MSG_ERROR_NULL_POINTER,
	MSG_ERROR_PROGRAM_INVOCATION,
	MSG_ERROR_OUT_OF_MEMORY,
	MSG_ERROR_INVALID_INPUT_POSITION,
	MSG_ERROR_INPUT_FILE_NOT_FOUND,
	MSG_ERROR_XML_EXPORTER_NOT_SETTED,
	MSG_ERROR_CSV_EXPORTER_NOT_SETTED
};

status_t errors_printer (status_t status)
{
	fprintf(stderr, "%s\n", errors[status]);

	return OK;
}
