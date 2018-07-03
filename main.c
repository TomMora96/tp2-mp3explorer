/* main.c */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "main.h"
#include "mp3explorer.h"
#include "types.h"
#include "errors.h"
#include "ADT_Track.h"
#include "ADT_Vector.h"
#include "config.h"
#include "mp3.h"
#include "xml.h"
#include "csv.h"

char *output_formats[] = {
	OUTPUT_FORMAT_CSV_STR,
	OUTPUT_FORMAT_XML_STR
};

extern config_t config;

int main (int argc, char *argv[])
{
	status_t st;
	ADT_Vector_t * ptr_track_vector;
	FILE * fo;


	if ((st = validate_arguments(argc, argv, &config)) != OK)
	{
		print_errors(st);
		return st;
	}

	if ((fo = fopen(config.output_file_name, "wt")) == NULL)
		return ERROR_INPUT_FILE_NOT_FOUND;

	if ((st = process_init_vector(&ptr_track_vector, &config)) != OK)
	{
		fclose(fo);
		print_errors(st);
		return st;
	}

	if ((st = process_mp3_files(argv, argc, &ptr_track_vector, fo)) != OK)
	{
		fclose(fo);
		print_errors(st);
		return st;
	}

	if (fclose(fo) == EOF)
	{
		print_errors(ERROR_CLOSE_FILES);
		return ERROR_CLOSE_FILES;
	}

	return OK;
}

/* función que valida argumentos. */
status_t validate_arguments (int argc, char *argv[], config_t *config)
{	
	size_t i = 0;
	bool_t output_format_is_valid = FALSE;
	bool_t sort_criteron_is_valid = FALSE;

	if (argv == NULL || config == NULL)
		return ERROR_NULL_POINTER;

	if (argc <= MIN_CMD_ARGS)
		return ERROR_PROGRAM_INVOCATION;

	if (strcmp(argv[CMD_ARG_OUTPUT_FORMAT_TOKEN_POS], FORMAT_TOKEN))
		return ERROR_PROGRAM_INVOCATION;

	if (strcmp(argv[CMD_ARG_SORTING_CRITERION_TOKEN_POS], SORTING_CRIETERION_TOKEN))
		return ERROR_PROGRAM_INVOCATION;

	if (strcmp(argv[CMD_ARG_OUTPUT_FILE_TOKEN_POS], OUTPUT_FILE_TOKEN))
		return ERROR_PROGRAM_INVOCATION;


	for(i = 0; i < MAX_OUTPUT_FORMATS && output_format_is_valid == FALSE; i++)
	{
		if(!strcmp(argv[CMD_ARG_OUTPUT_FORMAT_VALUE_POS], output_formats[i]))
		{
			config -> output_format = i;
			output_format_is_valid = TRUE;
		}
	}

	if(output_format_is_valid == FALSE)
		return ERROR_PROGRAM_INVOCATION;

	for(i = 0; i < MAX_TRACK_COMPARATOR && sort_criteron_is_valid == FALSE; i++)
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

	return OK;
}

