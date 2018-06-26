/* errors.c */

#include <stdio.h>

#include "types.h"
#include "errors.h"

char *errors[] = {
	MSG_OK,
	MSG_ERROR_NULL_POINTER,
	MSG_ERROR_PROGRAM_INVOCATION,
	MSG_ERROR_OUT_OF_MEMORY
};

status_t errors_printer (status_t status)
{
	fprintf(stderr, "%s\n", errors[status]);

	return OK;
}
