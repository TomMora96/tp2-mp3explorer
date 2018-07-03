/* mp3explorer.c */

#include <stdio.h>
#include <stdlib.h>

#include "main.h"
#include "types.h"
#include "errors.h"
#include "ADT_Vector.h"
#include "ADT_Track.h"
#include "config.h"
#include "mp3explorer.h"
#include "csv.h"
#include "xml.h"

extern char * xml_context[];
extern char csv_context;

status_t (*vector_exporters[MAX_VECTOR_EXPORTERS]) (const void *, const void *, FILE *)  = {
	(*ADT_Vector_export_as_csv),
	(*ADT_Vector_export_as_xml)
};

int (*track_comparators[MAX_TRACK_COMPARATOR]) (const void *, const void *) = {
	ADT_Track_compare_by_name,
    ADT_Track_compare_by_artist,
    ADT_Track_compare_by_genre,
};

char *sort_criteria[MAX_SORT_CRITERIA] = {
	SORT_BY_NAME_STR,
	SORT_BY_ALBUM_STR,
	SORT_BY_GENRE_STR
}; 

status_t process_init_vector (ADT_Vector_t ** ptr_track_vector, config_t *config)
{
	status_t st;

	if((st = ADT_Vector_new(ptr_track_vector)) != OK)
		return st;

	if((st = ADT_Vector_set_csv_exporter(*ptr_track_vector, *ADT_Track_export_as_csv)) != OK)
	{
		ADT_Vector_delete(ptr_track_vector);
		return st;
	}

	if((st = ADT_Vector_set_xml_exporter(*ptr_track_vector, *ADT_Track_export_as_xml)) != OK)
	{
		ADT_Vector_delete(ptr_track_vector);
		return st;
	}

	if((st = ADT_Vector_set_destructor(*ptr_track_vector, *ADT_Track_destroy)) != OK)
	{
		ADT_Vector_delete(ptr_track_vector);
		return st;
	}
	
	if((st = ADT_Vector_set_comparator(*ptr_track_vector, *(track_comparators[config -> sort_criterion]))) != OK)
	{
		ADT_Vector_delete(ptr_track_vector);
		return st;
	}

	return OK;
}

status_t load_mp3_tracks_from_files(char ** mp3_files_arr, size_t arr_len, ADT_Vector_t * ptr_track_vector)
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
			ADT_Vector_delete(&ptr_track_vector);
			return st;
		}

		if ((st = ADT_Vector_add_element(ptr_track_vector, ptr_track)) != OK)
		{
			fclose(mp3_file);
			ADT_Vector_delete(&ptr_track_vector);
			return st;
		}

		fclose(mp3_file);
	}

	return OK;
}

/* argv - CMD_MIN_INPUT_ARGS -> Arreglo de los nombres de los archivos mp3 */
/* argc - CMD_MIN_INPUT_ARGS: Cantidad de archivos mp3 */
status_t process_mp3_files(char * argv[], int argc, ADT_Vector_t ** ptr_track_vector, FILE * fo)
{
	status_t st;


	if ((st = load_mp3_tracks_from_files(argv + MIN_CMD_ARGS, argc - MIN_CMD_ARGS, *ptr_track_vector)) != OK)
		return st;

	ADT_Vector_sort(*ptr_track_vector);

	switch (config.output_format)
	{
		case DOC_TYPE_CSV:
		if((st = ADT_Vector_export_as_csv(*ptr_track_vector, (void *) &csv_context, fo)) != OK)
			return st;
		break;

		case DOC_TYPE_XML:
		if((st = ADT_Vector_export_as_xml(*ptr_track_vector, (void *) &xml_context, fo)) != OK)
			return st;
		break;

		default:
		return ERROR_PROGRAM_INVOCATION;
		break;	
	}

	return OK;
}
