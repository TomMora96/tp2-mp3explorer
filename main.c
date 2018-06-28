/* main.c */

#include <stdio.h>
#include <string.h>

#include "config.h"
#include "types.h"
#include "main.h"
#include "errors.h"
#include "ADT_Vector.h"
#include "ADT_Track.h"

char *output_formats[] = {
	OUTPUT_FORMAT_CSV_STR,
	OUTPUT_FORMAT_XML_STR
};

char *sort_criteria[] = {
	SORT_BY_NAME_STR,
	SORT_BY_ALBUM_STR,
	SORT_BY_GENRE_STR
};
/* agrego esto */

status_t (*track_exporters[2]) (const void *, const void *, FILE *) = 
{
	(* ADT_Track_export_as_csv),
	(* ADT_Track_export_as_xml)
};

/* hasta aca */


extern config_t config;

int main (int argc, char *argv[])
{
	status_t st;
	char * files_names[MAX_NUMBER_FILES];

	if ((st = validate_arguments(argc, argv, &config)) != OK)
	{
		errors_printer(st);
		return st;
	}
	/*

	if ((st = arguments_to_vector(&config, )))

	status_t arguments_to_vector (config_t config, char * files_names[])
*/

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


status_t arguments_to_vector (config_t config, char * files_names[])
{
	status_t st;
	ADT_Vector_t * ptr_track_vector;
	ADT_Track_t * ptr_track;
	FILE * file;
	size_t amf = config.amount_files, i;
	char csv_context = '|';

	char * xml_context[] = {
		"<?xml version=\"1.0\" ?>", 
		"tracks", 
		"track", 
		"name", 
		"artist", 
		"genre"
	};

	if((st = ADT_Vector_new(&ptr_track_vector)) != OK)
	{
		errors_printer(st);
		return st;
	}

	if((st = ADT_Vector_set_csv_exporter(ptr_track_vector, *ADT_Track_export_as_csv)) != OK)
	{
		errors_printer(st);
		return st;
	}

	if((st = ADT_Vector_set_xml_exporter(ptr_track_vector, *ADT_Track_export_as_xml)) != OK)
	{
		errors_printer(st);
		return st;
	}

	if((st = ADT_Vector_set_destructor(ptr_track_vector, *ADT_Track_destroy)) != OK)
	{
		errors_printer(st);
		return st;
	}

	for (i = 0; i < amf; i++)
	{
		if ((file = fopen(files_names[i], "rb")) == NULL)
			return ERROR_INPUT_FILE_NOT_FOUND;

		if ((st = ADT_Track_new_from_mp3_file(file, &ptr_track)))
		{
			fclose(file);
			ADT_Vector_delete(&ptr_track_vector);
			return st;
		}

		if ((st = ADT_Vector_add_element(ptr_track_vector, (void *) &ptr_track)) != OK)
		{
			fclose(file);
			ADT_Vector_delete(&ptr_track_vector);
			return st;
		}

		switch (config.output_format)
		{
			case output_format_csv:
			if((st = ADT_Vector_export_as_csv(ptr_track_vector, (void *) &csv_context, stdout)) != OK)
				{
					errors_printer(st);
					return st;
				}
			break;

			case output_format_xml:
			if((st = ADT_Vector_export_as_xml(ptr_track_vector, (void *) &xml_context, stdout)) != OK)
				{
					errors_printer(st);
					return st;
				}
			break;

			default:
			return ERROR_PROGRAM_INVOCATION;
		}
	}
	return OK;
}

