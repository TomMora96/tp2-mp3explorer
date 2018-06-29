#include <stdio.h>
#include <string.h>

#include "types.h"
#include "errors.h"
#include "ADT_Track.h"
#include "ADT_Vector.h"
#include "config.h"
#include "mp3.h"
#include "xml.h"
#include "csv.h"

extern char * xml_context[];
extern char csv_context;

status_t (*track_exporters[2]) (const void *, const void *, FILE *)  = 
{
	(*ADT_Track_export_as_csv),
	(*ADT_Track_export_as_xml)
};

int main(void)
{
	status_t st;
	ADT_Vector_t * ptr_track_vector;
	ADT_Track_t * ptr_track1;
	ADT_Track_t * ptr_track2;
	ADT_Track_t * ptr_track3, * ptr_track4, *ptr_track5;
	FILE * f1;
	FILE * f2;
	FILE * f3, *f4, *f5;

	if ((f1 = fopen("track1.mp3", "rb")) == NULL)
		return ERROR_INPUT_FILE_NOT_FOUND;

	if ((f2 = fopen("track2.mp3", "rb")) == NULL)
		return ERROR_INPUT_FILE_NOT_FOUND;

	if ((f3 = fopen("track3.mp3", "rb")) == NULL)
		return ERROR_INPUT_FILE_NOT_FOUND;

	if ((f4 = fopen("track4.mp3", "rb")) == NULL)
		return ERROR_INPUT_FILE_NOT_FOUND;

	if ((f5 = fopen("track5.mp3", "rb")) == NULL)
		return ERROR_INPUT_FILE_NOT_FOUND;

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
	
	if((st = ADT_Vector_set_comparator(ptr_track_vector, *ADT_Track_compare_by_artist)) != OK)
	{
		errors_printer(st);
		return st;
	}

	if((st = ADT_Track_new_from_mp3_file(f1, &ptr_track1)) != OK)
	{
		errors_printer(st);
		return st;
	}

	if((st = ADT_Track_new_from_mp3_file(f2, &ptr_track2)) != OK)
	{
		errors_printer(st);
		return st;
	}

	if((st = ADT_Track_new_from_mp3_file(f3, &ptr_track3)) != OK)
	{
		errors_printer(st);
		return st;
	}

	if((st = ADT_Track_new_from_mp3_file(f4, &ptr_track4)) != OK)
	{
		errors_printer(st);
		return st;
	}

	if((st = ADT_Track_new_from_mp3_file(f5, &ptr_track5)) != OK)
	{
		errors_printer(st);
		return st;
	}

	if((st = ADT_Vector_add_element(ptr_track_vector, ptr_track1)) != OK)
	{
		errors_printer(st);
		return st;
	}
	if((st = ADT_Vector_add_element(ptr_track_vector, ptr_track2)) != OK)
	{
		errors_printer(st);
		return st;
	}

	if((st = ADT_Vector_add_element(ptr_track_vector, ptr_track3)) != OK)
	{
		errors_printer(st);
		return st;
	}


	if((st = ADT_Vector_add_element(ptr_track_vector, ptr_track4)) != OK)
	{
		errors_printer(st);
		return st;
	}

	if((st = ADT_Vector_add_element(ptr_track_vector, ptr_track5)) != OK)
	{
		errors_printer(st);
		return st;
	}

	if((st = ADT_Vector_sort(ptr_track_vector)) != OK)
	{
		errors_printer(st);
		return st;
	}

	if((st = ADT_Vector_export_as_csv(ptr_track_vector, (void *) &csv_context, stdout)) != OK)
	{
		errors_printer(st);
		return st;
	}
	if((st = ADT_Vector_export_as_xml(ptr_track_vector, (void *) &xml_context, stdout)) != OK)
	{
		errors_printer(st);
		return st;
	}

	return OK;
}

