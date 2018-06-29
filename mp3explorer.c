/* mp3explorer.c */

#include <stdio.h>
#include <stdlib.h>

#include "main.h"
#include "types.h"
#include "errors.h"
#include "ADT_Vector.h"
#include "ADT_Track.h"
#include "config.h" 

int (*track_comparators[MAX_SORTING_CRITERIA]) (const void *, const void *) =
{
	*ADT_Track_compare_by_name,
    *ADT_Track_compare_by_artist,
    *ADT_Track_compare_by_genre,
};

status_t load_vector (ADT_Vector_t ** ptr_track_vector, config_t *config)
{
	status_t st;
	ADT_Track_t * ptr_track;
	FILE * file;
	size_t amf = config -> amount_files, i;

	if((st = ADT_Vector_new(ptr_track_vector)) != OK)
	{
		errors_printer(st);
		return st;
	}

	if((st = ADT_Vector_set_csv_exporter(*ptr_track_vector, *ADT_Track_export_as_csv)) != OK)
	{
		errors_printer(st);
		return st;
	}
	if((st = ADT_Vector_set_xml_exporter(*ptr_track_vector, *ADT_Track_export_as_xml)) != OK)
	{
		errors_printer(st);
		return st;
	}
	if((st = ADT_Vector_set_destructor(*ptr_track_vector, *ADT_Track_destroy)) != OK)
	{
		errors_printer(st);
		return st;
	}
	
	if((st = ADT_Vector_set_comparator(*ptr_track_vector, *(track_comparators[config -> sort_criterion]))) != OK)
	{
		errors_printer(st);
		return st;
	}


	for (i = 0; i < amf; i++)
	{
		if ((file = fopen(config -> input_files_names[i], "rb")) == NULL)
			return ERROR_INPUT_FILE_NOT_FOUND;

		if ((st = ADT_Track_new_from_mp3_file(file, &ptr_track)))
		{
			fclose(file);
			ADT_Vector_delete(ptr_track_vector);
			return st;
		}

		if ((st = ADT_Vector_add_element(*ptr_track_vector, ptr_track)) != OK)
		{
			fclose(file);
			ADT_Vector_delete(ptr_track_vector);
			return st;
		}

		fclose(file);
	}

	return OK;
}
