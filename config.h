/* config.h */

#ifndef CONFIG__H
#define CONFIG__H

#include "types.h"

typedef struct {
	output_format_t output_format;
	sort_criteria_t sort_criterion;
	char * output_file_name;
	size_t input_files_amount;
	char ** input_files_names;
} config_t;

#endif
