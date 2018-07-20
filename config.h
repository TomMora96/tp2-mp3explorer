/* config.h */

#ifndef CONFIG__H
#define CONFIG__H

#include <stdio.h>

#include "types.h"
#include "mp3.h"

typedef enum {
	SORT_BY_NAME = 0,
	SORT_BY_ARTIST = 1,
	SORT_BY_GENRE = 2
} sort_criteria_t;

typedef struct {
	doc_type_t output_format;
	sort_criteria_t sort_criterion;
	char * output_file_name;
} config_t;


#endif
