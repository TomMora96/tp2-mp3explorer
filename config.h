/* config.h */

#ifndef CONFIG__H
#define CONFIG__H

#include <stdio.h>
#include "types.h"

typedef struct {
	doc_type_t output_format;
	sort_criteria_t sort_criterion;
	char * output_file_name;
} config_t;

#endif
