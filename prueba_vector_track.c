#include <stdio.h>
#include <string.h>

#include "types.h"
#include "errors.h"
#include "ADT_Track.h"
#include "ADT_Vector.h"

int main(void)
{
	status_t st;
	ADT_Vector_t * ptr_track_vector;
	ADT_Track_t * ptr_track1;
	ADT_Track_t * ptr_track2;

	if((st = ADT_Vector_new(&ptr_track_vector)) != OK)
	{
		errors_printer(st);
		return st;
	}
	
	if((st = ADT_Vector_set_csv_exporter(ADT_Track_export_as_csv)) != OK)
	{
		errors_printer(st);
		return st;
	}
	if((st = ADT_Vector_set_xml_exporter(*ADT_Track_export_as_xml)) != OK)
	{
		errors_printer(st);
		return st;
	}
	if((st = ADT_Vector_set_destructor(*ADT_Track_destroy)) != OK)
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