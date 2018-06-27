/* main.c */

#include <stdio.h>
#include <string.h>

#include "config.h"
#include "types.h"
#include "main.h"
#include "errors.h"
#include "ADT_Vector.h"

char *output_formats[] = {
	OUTPUT_FORMAT_CSV_STR,
	OUTPUT_FORMAT_XML_STR
};

char *sort_criteria[] = {
	SORT_BY_NAME_STR,
	SORT_BY_ALBUM_STR,
	SORT_BY_GENRE_STR
};

extern config_t config;

int main (int argc, char *argv[])
{
	status_t st;

	if((st = validate_arguments(argc, argv, &config)) != OK)
	{
		errors_printer(st);
		return st;
	}	

	return 0;
}

status_t validate_arguments (int argc, char *argv[], config_t *config)
{	
	size_t i = 0;
	bool_t output_format_is_valid = FALSE;
	bool_t sort_criteron_is_valid = FALSE;

	if (argv == NULL || config == NULL)
		return ERROR_NULL_POINTER;

	if (argc <= CMD_MIN_INPUT_ARGS)
		return ERROR_PROGRAM_INVOCATION;

	if (strcmp(argv[CMD_ARG_OUTPUT_FORMAT_TOKEN_POS], FORMAT_TOKEN))
		return ERROR_PROGRAM_INVOCATION;

	if (strcmp(argv[CMD_ARG_SORTING_CRITERION_TOKEN_POS], SORTING_CRIETERION_TOKEN))
		return ERROR_PROGRAM_INVOCATION;

	if (strcmp(argv[CMD_ARG_OUTPUT_FILE_TOKEN_POS], OUTPUT_FILE_TOKEN))
		return ERROR_PROGRAM_INVOCATION;


	for(i = 0; (i < MAX_OUTPUT_FORMATS) && (output_format_is_valid == FALSE); i++)
	{
		if(!strcmp(argv[CMD_ARG_OUTPUT_FORMAT_VALUE_POS], output_formats[i]))
		{
			config -> output_format = i;
			output_format_is_valid = TRUE;
		}
	}
	if(output_format_is_valid == FALSE)
		return ERROR_PROGRAM_INVOCATION;

	for(i = 0; i < MAX_SORTING_CRITERIA && sort_criteron_is_valid == FALSE; i++)
	{
		if(!strcmp(argv[CMD_ARG_SORTING_CRTIERION_VALUE_POS], sort_criteria[i]))
		{
			config -> sort_criterion = i;
			sort_criteron_is_valid = TRUE;
		}
	}
	
	if(sort_criteron_is_valid == FALSE)
		return ERROR_PROGRAM_INVOCATION;

	config -> output_file_name = argv[CMD_ARG_OUTPUT_FILE_VALUE_POS];

	config -> amount_files = argc - CMD_MIN_INPUT_ARGS;

	return OK;
}
