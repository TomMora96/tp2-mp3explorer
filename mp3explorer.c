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


/*Arreglos de punteros a función con las primitivas de exportadores de ADT_Vector.*/
status_t (*track_exporters[MAX_TRACK_EXPORTERS]) (const void *, const void *, FILE *)  = {
	(*ADT_Track_export_as_csv),
	(*ADT_Track_export_as_xml),
	(*ADT_Track_export_as_html)
};


/*Arreglos de punteros a función con las primitivas de comparación de ADT_Track.-*/
/*Lo utiliza set_track_vector para setear de que manera se deben comparar -------*/
/*los elementos del vector para ordenarlo según lo indicado por la configuración.*/
int (*track_comparators[MAX_TRACK_COMPARATORS]) (const void *, const void *) = {
	ADT_Track_compare_by_name,
    ADT_Track_compare_by_artist,
    ADT_Track_compare_by_genre,
};


status_t process_mp3_files(char * mp3_files_arr[], size_t arr_len, config_t *config, FILE * fo)
{
	ADT_Vector_t * ptr_track_vector;
	status_t st;

	if ((st = set_track_vector (&ptr_track_vector, config)) != OK)
		return st;

	if ((st = load_mp3_tracks_from_files(mp3_files_arr, arr_len, ptr_track_vector)) != OK)
	{
		ADT_Vector_delete(&ptr_track_vector);
		return st;
	}

	if ((st = ADT_Vector_sort(ptr_track_vector)) != OK)
	{
		ADT_Vector_delete(&ptr_track_vector);
		return st;
	}

	switch (config -> output_format)
	{
		case DOC_TYPE_CSV:
			if((st = ADT_Vector_export(ptr_track_vector, (void *) &csv_context, NULL, NULL, fo)) != OK)
			{
				ADT_Vector_delete(&ptr_track_vector);
				return st;
			}
			break;

		case DOC_TYPE_XML:
			if((st = ADT_Vector_export(ptr_track_vector, (void *) &xml_context, XML_HEADER, XML_FOOTER, fo)) != OK)
			{
				ADT_Vector_delete(&ptr_track_vector);
				return st;
			}
			break;

		default:
			ADT_Vector_delete(&ptr_track_vector);
			return ERROR_PROGRAM_INVOCATION;
	}

	ADT_Vector_delete(&ptr_track_vector);
	return OK;
}

/*Crea un ADT_Vector_t vacio y setea sus punteros a función según la configuración recivida por argumento.*/
/*Una vez utilizado el vector, debe llamarse a ADT_Vector_delete sobre el para liberar memoria.-----------*/
status_t set_track_vector (ADT_Vector_t ** ptr_track_vector, config_t *config)
{
	status_t st;

	if((st = ADT_Vector_new(ptr_track_vector)) != OK)
		return st;

	if((st = ADT_Vector_set_exporter(*ptr_track_vector, *(track_exporters[config -> output_format]))) != OK)
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
			return st;
		}

		if ((st = ADT_Vector_add_element(ptr_track_vector, ptr_track)) != OK)
		{
			fclose(mp3_file);
			return st;
		}

		fclose(mp3_file);
	}

	return OK;
}
