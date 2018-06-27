/* printer.c */

#include <stdio.h>
#include <string.h>

#include "types.h"
#include "ADT_Track.h"
#include "ADT_Vector.h"

#define XML_HEADER "xml_header.txt"


status_t ADT_Track_print_as_csv (const void * pv, const void * p_context, FILE * fo)
{
	ADT_Track_t * p = (ADT_Track_t *) pv;
	char delimiter = *((char *)p_context);
	char * str = NULL;
	unsigned char uc;
	status_t st;

	if (pv == NULL || p_context == NULL || fo == NULL)
		return ERROR_NULL_POINTER;

	if ((st = ADT_Track_get_name(p, str)) != OK)
		return st;
	fprintf(fo, "%s%c", str, delimiter);

	if ((st = ADT_Track_get_artist(p, str)) != OK)
		return st;
	fprintf(fo, "%s%c", str, delimiter);

	if ((st = ADT_Track_get_genre(p, &uc)) != OK)
		return st;
	fprintf(fo, "%u", uc);

	printf("\n");


	return OK;
}


status_t ADT_Vector_export_as_csv (FILE * fo, const void * v, const void * p_context)
{
	ADT_Vector_t * p = (ADT_Vector_t *) v;
	char delimiter = *((char *)p_context);
	size_t i, v_size;
	ADT_Track_t * track;

	if(fo == NULL || v == NULL)
		return ERROR_NULL_POINTER;

	v_size = ADT_Vector_get_size(p);

	for(i = 0; i < v_size; i++)
	{
		track = ADT_Vector_get_element(v, i);

		ADT_Track_print_as_csv(track, &delimiter, fo);
	}

	return OK;
}


status_t ADT_Track_print_as_xml (const void * pv, const void * p_context, FILE * fo)
{
	ADT_Track_t *p = (ADT_Track_t *) pv;
	char * str = NULL;
	unsigned char uc;
	status_t st;

	if (pv == NULL || p_context == NULL || fo == NULL)
		return ERROR_NULL_POINTER;

	if ((st = ADT_Track_get_name(p, str)) != OK)
		return st;
	fputs("<tracks>", fo);
	fputs("\t<track>", fo);
	fprintf(fo, "\t\t%s%s%s\n", "<name>", p -> name, "<name>");

	if ((st = ADT_Track_get_artist(p, str)) != OK)
		return st;
	fprintf(fo, "\t\t%s%s%s\n", "<artist>", p -> artist, "<artist>");

	if ((st = ADT_Track_get_genre(p, &uc)) != OK)
		return st;
	fprintf(fo, "\t\t%s%u%s\n", "<genre>", p -> genre, "<genre>");
	fputs("\t<track>", fo);

	return OK;
}


status_t ADT_Vector_export_as_xml (FILE * fo, const void * v, const void * p_context)
{

	ADT_Vector_t * p = (ADT_Vector_t *) v;
	FILE * file_header;
	int c;
	size_t i, v_size;
	ADT_Track_t * track;

	if ((file_header = fopen(XML_HEADER, "rt")) == NULL)
		return ERROR_INPUT_FILE_NOT_FOUND;

	while((c = fgetc(file_header)) != EOF && c)
		fputc(c, fo);

	fclose(file_header);

	v_size = ADT_Vector_get_size(p);

	for(i = 0; i < v_size; i++)
	{
		track = ADT_Vector_get_element (v, i);
		
		ADT_Track_print_as_xml(v, " NO SE QUE PONER AQUI ", fo);
	}

	return OK;
}

status_t export_format (FILE * output_file, ADT_Vector_t * v , exporter_t pf)
{
	status_t st;

	if (output_file == NULL || v == NULL || pf == NULL)
		return ERROR_NULL_POINTER;
	
	if ((st = (* pf) (output_file, v, DELIMITER_CSV)) != OK)
		return st;

	return OK;
}

