#include <stdio.h>
#include <string.h>

#include "types.h"
#include "errors.h"
#include "ADT_Track.h"
#include "ADT_Vector.h"
#include "config.h"
#include "mp3.h"

status_t (*track_exporters[2]) (const void *, const void *, FILE *)= 
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
	FILE * f1;
	FILE * f2;

	if ((f1 = fopen("track.mp3", "rb")) == NULL)
		return ERROR_INPUT_FILE_NOT_FOUND;

	if ((f2 = fopen("track.mp3", "rb")) == NULL)
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

	if((st = ADT_Vector_export_as_xml(ptr_track_vector, "SIN FUNCIONALIDAD", stdout)) != OK)
	{
		errors_printer(st);
		return st;
	}
	if((st = ADT_Vector_export_as_xml(ptr_track_vector, "SIN FUNCIONALIDAD", stdout)) != OK)
	{
		errors_printer(st);
		return st;
	}

	return OK;
}

