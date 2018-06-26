/* types.h */

#ifndef TYPES__H 
#define TYPES__H

typedef enum {
	OK,
	ERROR_NULL_POINTER,
	ERROR_PROGRAM_INVOCATION,
	ERROR_OUT_OF_MEMORY
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


typedef int (*comparator_t)(void * t1, void * t2);



#endif
