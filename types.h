/* types.h */

#ifndef TYPES__H 
#define TYPES__H

typedef enum {
	OK,
	ERROR_NULL_POINTER = 1,
	ERROR_PROGRAM_INVOCATION = 2,
	ERROR_OUT_OF_MEMORY = 3,
	ERROR_INVALID_INPUT_POSITION = 4,
	ERROR_INPUT_FILE_NOT_FOUND = 5,
	ERROR_XML_EXPORTER_NOT_SETTED = 6,
	ERROR_CSV_EXPORTER_NOT_SETTED = 7,
	ERROR_COMPARATOR_NOT_SETTED = 8,
	ERROR_INVALID_TRACK_PARAMETER = 9,
	ERROR_CLOSE_FILES = 10
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

typedef status_t (* destructor_t)(void **);
typedef status_t (* exporter_t)(const void *, const void *, FILE *);
typedef int (* comparator_t)(const void *, const void *);

#endif
