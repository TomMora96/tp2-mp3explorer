/* ADT_Vector.h */

#ifndef ADT_VECTOR__H
#define ADT_VECTOR__H

#include "types.h"
#define XML_HEADER "xml_header.txt"

#define ADT_INIT_CHOP 10
#define ADT_CHOP_SIZE 20

typedef struct {
	size_t size; /* es;ta es la cantidad de elementos que tiene el vector */
	size_t alloc_size; /* esta es la cantidad de elementos que puede tener el vector */
	void ** elements; /* tipo de dato en cada casillero del vector */
	destructor_t destructor;
	exporter_t xml_exporter;
	exporter_t csv_exporter;
	comparator_t comparator;
} ADT_Vector_t;

/*-------------------Constructors-------------------*/
status_t ADT_Vector_new (ADT_Vector_t ** pp);
status_t ADT_Vector_expand (ADT_Vector_t * v, size_t chop_size);

/*-------------------Destructors--------------------*/
status_t ADT_Vector_delete (ADT_Vector_t ** pp);

/*-------------------Getters------------------------*/
size_t ADT_Vector_get_size(const ADT_Vector_t *pp);
void * ADT_Vector_get_element(const ADT_Vector_t * v, size_t position);
bool_t ADT_Vector_is_empty(const ADT_Vector_t * v);

/*-------------------Adder-------------------------*/
status_t ADT_Vector_add_element(ADT_Vector_t * v, void * element);


/*-------------------Exporters---------------------*/
status_t ADT_Vector_export_as_csv(const void * v, const void * context, FILE * fo);
status_t ADT_Vector_export_as_xml (const void * v, const void * context, FILE * fo);


/*-------------------Sorter------------------------*/
status_t ADT_Vector_sort(ADT_Vector_t * v);


/*-------------------Setters------------------------*/
status_t ADT_Vector_set_destructor (ADT_Vector_t * v, destructor_t pf);
status_t ADT_Vector_set_csv_exporter(ADT_Vector_t * v, exporter_t pf);
status_t ADT_Vector_set_xml_exporter(ADT_Vector_t * v, exporter_t pf);
status_t ADT_Vector_set_comparator(ADT_Vector_t * v, comparator_t pf);


#endif
