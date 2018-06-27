/* ADT_Vector.h */

#ifndef ADT_VECTOR__H
#define ADT_VECTOR__H

#include "types.h"

#define ADT_INIT_CHOP 10
#define ADT_CHOP_SIZE 20

typedef struct {
	size_t size; /* es;ta es la cantidad de elementos que tiene el vector */
	size_t alloc_size; /* esta es la cantidad de elementos que puede tener el vector */
	void ** elements; /* tipo de dato en cada casillero del vector */
	destructor_t destructor;
} ADT_Vector_t;

status_t ADT_Vector_new (ADT_Vector_t ** pp);
status_t ADT_Vector_delete (ADT_Vector_t ** pp, destructor_t pf);
status_t ADT_Vector_expand (ADT_Vector_t * v, size_t chop_size);
size_t ADT_Vector_get_size(ADT_Vector_t *pp);
void * ADT_Vector_get_element(const ADT_Vector_t * v, size_t position);
status_t ADT_Vector_add_element(ADT_Vector_t * v, void * element);
bool_t ADT_Vector_is_empty(const ADT_Vector_t * v);
status_t ADT_Vector_set_destructor (ADT_Vector_t * v, destructor_t pf);

#endif
