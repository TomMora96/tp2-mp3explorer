/* types.h */

#ifndef TYPES__H 
#define TYPES__H

typedef enum {
	OK,
	ERROR_NULL_POINTER = 1,
	ERROR_PROGRAM_INVOCATION = 2,
	ERROR_OUT_OF_MEMORY = 3,
	ERROR_INVALID_INPUT_POSITION = 4,
	ERROR_INPUT_FILE_NOT_FOUND = 5
} status_t;

typedef enum {
	output_format_csv = 0,
	output_format_xml = 1
} output_format_t;


typedef enum {
	sort_by_name = 0,
	sort_by_artist = 1,
	sort_by_genre = 2
} sort_criteria_t;

typedef enum {
	TRUE,
	FALSE
} bool_t;

typedef status_t (*destructor_t)(void **);
typedef status_t (*printer_t)(const void * pv, const void * p_context, FILE * fi);

#endif
