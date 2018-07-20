/* types.h */

#ifndef TYPES__H 
#define TYPES__H

#include <stdio.h>

typedef enum {
	OK,
	ERROR_NULL_POINTER = 1,
	ERROR_PROGRAM_INVOCATION = 2,
	ERROR_OUT_OF_MEMORY = 3,
	ERROR_INVALID_INPUT_POSITION = 4,
	ERROR_INPUT_FILE_NOT_FOUND = 5,
	ERROR_EXPORTER_NOT_SET = 6,
	ERROR_COMPARATOR_NOT_SET = 8,
	ERROR_INVALID_TRACK_PARAMETER = 9,
	ERROR_OUT_OF_DISK_SPACE = 10,
	ERROR_HEADER_FILE_NOT_FOUND = 11,
	ERROR_FOOTER_FILE_NOT_FOUND = 12
} status_t;

typedef enum {
	DOC_TYPE_CSV = 0,
	DOC_TYPE_XML = 1,
	DOC_TYPE_HTML = 2
} doc_type_t;

typedef enum {
	TRUE,
	FALSE
} bool_t;

typedef status_t (* destructor_t)(void **);
typedef status_t (* exporter_t)(const void *, const void *, FILE *);
typedef int (* comparator_t)(const void *, const void *);

#endif
