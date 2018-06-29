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

status_t initialize_vector (ADT_Vector_t ** ptr_track_vector, config_t *config)
{
	status_t st;

	if((st = ADT_Vector_new(ptr_track_vector)) != OK)
		return st;

	if((st = ADT_Vector_set_csv_exporter(*ptr_track_vector, *ADT_Track_export_as_csv)) != OK)
		return st;

	if((st = ADT_Vector_set_xml_exporter(*ptr_track_vector, *ADT_Track_export_as_xml)) != OK)
		return st;

	if((st = ADT_Vector_set_destructor(*ptr_track_vector, *ADT_Track_destroy)) != OK)
		return st;
	
	if((st = ADT_Vector_set_comparator(*ptr_track_vector, *(track_comparators[config -> sort_criterion]))) != OK)
		return st;

	return OK;
}

status_t load_mp3_tracks_from_files_to_vector(char ** mp3_files_arr, size_t arr_len, ADT_Vector_t ** ptr_track_vector)
{
	ADT_Track_t * ptr_track;
	FILE * mp3_file;
	size_t i;
	status_t st;

	if(mp3_files_arr == NULL || ptr_track_vector == NULL)
		return ERROR_NULL_POINTER;

	for (i = 0; i < arr_len; i++)
	{
		if ((mp3_file = fopen(mp3_files_arr[i], "rb")) == NULL)
			return ERROR_INPUT_FILE_NOT_FOUND;

		if ((st = ADT_Track_new_from_mp3_file(mp3_file, &ptr_track)))
		{
			fclose(mp3_file);
			ADT_Vector_delete(ptr_track_vector);
			return st;
		}

		if ((st = ADT_Vector_add_element(*ptr_track_vector, ptr_track)) != OK)
		{
			fclose(mp3_file);
			ADT_Vector_delete(ptr_track_vector);
			return st;
		}

		fclose(mp3_file);
	}

	return OK;
}
