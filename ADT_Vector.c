/* ADT_Vector.c */

#include <stdio.h>
#include <stdlib.h>

#include "ADT_Vector.h"
#include "types.h"
#include "xml.h"
#include "csv.h"


/*-------------------Constructors-------------------*/
status_t ADT_Vector_new (ADT_Vector_t ** pp) 
{
	size_t i;

	if (pp == NULL)
		return ERROR_NULL_POINTER;

	if ((*pp = (ADT_Vector_t *) malloc(sizeof(ADT_Vector_t))) == NULL)
		return ERROR_OUT_OF_MEMORY;

	if (((*pp) -> elements = (void **) malloc(ADT_INIT_CHOP * sizeof(void *))) == NULL)
	{
		free(*pp);
		*pp = NULL;
		return ERROR_OUT_OF_MEMORY;
	}

	(*pp) -> alloc_size = ADT_INIT_CHOP;
	(*pp) -> size = 0;

	(*pp) -> destructor = NULL;
	(*pp) -> xml_export = NULL;
	(*pp) -> csv_export = NULL;
	(*pp) -> comparator = NULL;

	for (i = 0; i < ADT_INIT_CHOP; i++)
		((*pp) -> elements)[i] = NULL;

	return OK;
}

/* Primero verificamos que haya memoria para aumentar 
el numero de elementos que puede almacenar el vector y 
su longitud */
status_t ADT_Vector_Expand (ADT_Vector_t * v, size_t new_size)
{
	void ** aux;

	if(v == NULL)
		return ERROR_NULL_POINTER;

	if(new_size == 0)
		return ERROR_OUT_OF_MEMORY;

	if((aux = (void *) realloc(v -> elements, (v -> alloc_size + new_size) * sizeof(void *))) == NULL)
		return ERROR_OUT_OF_MEMORY;

	v -> elements = aux;
	v -> alloc_size += new_size;
		
	return OK;
}


/*-------------------Destructors--------------------*/
status_t ADT_Vector_delete (ADT_Vector_t ** pp)
{
	size_t i;
	status_t status;

	if (pp == NULL)
		return ERROR_NULL_POINTER;

	for (i = 0; i < (* pp) -> size; i++)
	{
		if ((status = ((*pp) -> destructor)((* pp) -> elements[i])) != OK)
			return status;

		(* pp) -> elements[i] = NULL;
	}

	free((* pp) -> elements);
	(* pp) -> elements = NULL;
	free(* pp);
	* pp = NULL;

	return OK;

}


/*-------------------Getters------------------------*/
size_t ADT_Vector_get_size(const ADT_Vector_t *pv)
{
	return pv -> size;
}

void * ADT_Vector_get_element(const ADT_Vector_t * v, size_t position)
{
	if (v == NULL)
		return NULL;

	if (position > v -> size)
		return NULL;

	return v -> elements[position];
}

bool_t ADT_Vector_is_empty (const ADT_Vector_t * v)
{
	return (v -> size) ? FALSE : TRUE;
}


/*-------------------Adder-------------------------*/
status_t ADT_Vector_add_element(ADT_Vector_t * v, void * element)
{
	void ** aux;
	
	if(v == NULL || element == NULL)
		return ERROR_NULL_POINTER;
	
	if(v -> size == v -> alloc_size)
	{
		if((aux = (void **) realloc(v -> elements, (v -> alloc_size + ADT_CHOP_SIZE) * sizeof(void *))) == NULL)
			return ERROR_OUT_OF_MEMORY;

		v -> elements = aux;
		v -> alloc_size += ADT_CHOP_SIZE;	
	}
	
	(v -> elements)[v->size]=element;
	(v -> size)++;
	
	return OK;
}


/*-------------------Exporters---------------------*/
status_t ADT_Vector_export_as_csv (const void * v, const void * p_context, FILE * fo)
{
	ADT_Vector_t * p = (ADT_Vector_t *) v;
	size_t i, v_size;
	void * element;


	if(fo == NULL || v == NULL || p_context == NULL)
		return ERROR_NULL_POINTER;

	if(p -> csv_export == NULL)
		return ERROR_CSV_EXPORTER_NOT_SET;

	v_size = ADT_Vector_get_size(p);

	for(i = 0; i < v_size; i++)
	{
		element = ADT_Vector_get_element(v, i);
		(p -> csv_export)(element, p_context, fo);
	}

	return OK;
}

status_t ADT_Vector_export_as_xml (const void * v, const void * p_context, FILE * fo)
{
	FILE * header_file, * footer_file;
	int c;
	size_t i, vec_size;
	ADT_Vector_t * p = (ADT_Vector_t *) v;
	char * * context = (char * *) p_context;
	void * element;

	if((header_file = fopen(XML_HEADER, "rt")) == NULL)
		return ERROR_XML_HEADER;

	while((c = fgetc(header_file)) != EOF && c)
		fputc(c, fo);

	fclose(header_file);

	vec_size = p -> alloc_size;

	for(i = 0; i < vec_size; i++)
	{
		element = ADT_Vector_get_element (v, i);		
		(p -> xml_export)(element, context, fo);
	}

	if((footer_file = fopen(XML_FOOTER, "rt")) == NULL)
		return ERROR_XML_FOOTER;

	while((c = fgetc(footer_file)) != EOF && c)
		fputc(c, fo);

	fclose(footer_file);

	return OK;
}


/*-------------------Sorter-------------------------*/
status_t ADT_Vector_sort(ADT_Vector_t * v)
{
	if(v == NULL)
		return ERROR_NULL_POINTER;

	if(v -> comparator == NULL)
		return ERROR_COMPARATOR_NOT_SET;

	qsort(v -> elements, v -> size, sizeof(v -> elements[0]), v -> comparator);

	return OK;
}


/*-------------------Setters------------------------*/
status_t ADT_Vector_set_destructor (ADT_Vector_t * v, destructor_t pf)
{
	if (v == NULL)
		return ERROR_NULL_POINTER;

	(v -> destructor) = pf;

	return OK;
}

status_t ADT_Vector_set_csv_export(ADT_Vector_t * v, exporter_t pf)
{
	if(v == NULL || pf == NULL)
		return ERROR_NULL_POINTER;
	
	v -> csv_export = pf;

	return OK;

}

status_t ADT_Vector_set_xml_export(ADT_Vector_t * v, exporter_t pf)
{
	if(v == NULL || pf == NULL)
		return ERROR_NULL_POINTER;
	
	v -> xml_export = pf;

	return OK;

}

status_t ADT_Vector_set_comparator(ADT_Vector_t * v, comparator_t pf)
{
	if(v == NULL || pf == NULL)
		return ERROR_NULL_POINTER;
	
	v -> comparator = pf;

	return OK;
}
