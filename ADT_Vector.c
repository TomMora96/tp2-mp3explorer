/* ADT_Vector.c */

#include <stdio.h>
#include <stdlib.h>

#include "ADT_Vector.h"
#include "types.h"

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

	for (i = 0; i < ADT_INIT_CHOP; i++)
		((*pp) -> elements)[i] = NULL;

	return OK;
}

status_t ADT_Vector_delete (ADT_Vector_t ** pp, destructor_t pf)
{
	size_t i;
	status_t status;

	if (pp == NULL)
		return ERROR_NULL_POINTER;

	for (i = 0; i < (* pp) -> size; i++)
	{
		if ((status = (* pf)((* pp) -> elements[i])) != OK)
			return status;

		(* pp) -> elements[i] = NULL;
	}

	free((* pp) -> elements);
	(* pp) -> elements = NULL;
	free(* pp);
	* pp = NULL;

	return OK;

}

status_t ADT_Vector_expand (ADT_Vector_t * v, size_t chop_size)
{
	void ** aux;

	if(v == NULL)
		return ERROR_NULL_POINTER;

	if(chop_size == 0)
		return ERROR_OUT_OF_MEMORY;

	if((aux = (void *) realloc(v -> elements, (v -> alloc_size + chop_size) * sizeof(void *))) == NULL)
		return ERROR_OUT_OF_MEMORY;

	v -> elements = aux;
	v -> alloc_size += chop_size;
		
	return OK;
}

size_t ADT_Vector_get_size(ADT_Vector_t *pv)
{
	return pv -> size;
}

void * ADT_Vector_get_element(const ADT_Vector_t * v, size_t position)
{
	if (v == NULL)
		return ERROR_NULL_POINTER;

	if (position > v -> size)
		return ERROR_INVALID_INPUT_POSITION;

	return v -> elements[position];
}

status_t ADT_Vector_add_element(ADT_Vector_t * v, void * element)
{
	void ** aux;
	
	if(v == NULL || element == NULL)
		return ERROR_NULL_POINTER;
	
	if(v -> size == v -> alloc_size)
	{
		if((aux = (void **) realloc(v -> elements, (v -> alloc_size + ADT_CHOP_SIZE) * sizeof(void *))) == NULL)
			/* la destruccion tiene que ser en el main */
			return ERROR_OUT_OF_MEMORY;

		v -> elements = aux;
		v -> alloc_size += ADT_CHOP_SIZE;	
	}
	
	(v -> elements)[v->size]=element;
	(v -> size)++;
	
	return OK;
}

bool_t ADT_Vector_is_empty (const ADT_Vector_t * v)
{
	return (v -> size) ? FALSE : TRUE;
}

status_t ADT_Vector_set_destructor (ADT_Vector_t * v, destructor_t pf)
{
	if (v == NULL)
		return ERROR_NULL_POINTER;

	(v -> destructor) = pf;

	return OK;
}
