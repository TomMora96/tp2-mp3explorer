/* ADT_Vector.h */

#ifndef ADT_VECTOR__H
#define ADT_VECTOR__H

#include "types.h"

#define ADT_VECTOR_INIT_CHOP 10
#define ADT_VECTOR_CHOP_SIZE 20

typedef struct {
	size_t size;
	size_t alloc_size;
	void ** elements;
	destructor_t destructor;
	exporter_t exporter;
	comparator_t comparator;
} ADT_Vector_t;

/*-------------------Constructors-------------------*/

/*ADT_Vector_new: Crea un vector vacio y con sus campos de punteros a función incializados en NULL.---------------*/
/*Asigna memoria inicial para la cantidad de elementos definida por ADT_VECTOR_INIT_CHOP.-------------------------*/
/*Para agregar elementos que superen esta asignación inicial no es necesario pedir memoria manualmente,-----------*/
/*ADT_Vector_add() se encarga de pedir más memoria de ser necesario.----------------------------------------------*/
/*Para llamar a las primitivas que involucran a dichos campos primero deben setearse------------------------------*/
/*los punteros a función a utilizar. Una vez utilizado, el vector debe eliminarse llamando a ADT_Vector_destroy().*/
status_t ADT_Vector_new (ADT_Vector_t ** pp);

/*ADT_Vector_expand: asigna mas memoria para el vector.----------*/
/*Utiliza estrategia de crecimiento incremental------------------*/
/*usando la macro ADT_VECTOR_CHOP_SIZE como valor del incremento.*/
status_t ADT_Vector_expand (ADT_Vector_t * v);

/*-------------------Destructors--------------------*/
status_t ADT_Vector_delete (ADT_Vector_t ** pp);

/*-------------------Getters------------------------*/
size_t ADT_Vector_get_size(const ADT_Vector_t *pp);

/*ADT_Vector_get_element: Devuelve un acceso físico al elemento del vector.*/
void * ADT_Vector_get_element(const ADT_Vector_t * v, size_t position);
bool_t ADT_Vector_is_empty(const ADT_Vector_t * v);

/*-------------------Adder-------------------------*/
status_t ADT_Vector_add_element(ADT_Vector_t * v, void * element);


/*-------------------Exporter---------------------*/
/*ADT_Vector_export: Exporta los elementos del vector segun el formato determinado por la función seteada en el campo exporter.*/
/*Argumentos:------------------------------------------------------------------------------------------------------------------*/
/*-------- v: Puntero al vector a exportar. -----------------------------------------------------------------------------------*/
/*-------- p_context: Puntero al contexto de exportación. Debe pasarse casteado como (void *). --------------------------------*/
/*------------------- Las funciones exporter_t se encargan castearlo al tipo de dato adecuado. --------------------------------*/
/*-------- header_file_name: Nombre del archivo de donde se importa el header del archivo de salida. --------------------------*/
/*------------------- Si se quiere exportar sin header pasar NULL como argumento. ---------------------------------------------*/
/*-------- footer_file_name: Nombre del archivo de donde se importa el footer del archivo de salida. --------------------------*/
/*------------------- Si se quiere exportar sin footer pasar NULL como argumento. ---------------------------------------------*/
/*-------- fo: Archivo de salida. ---------------------------------------------------------------------------------------------*/
status_t ADT_Vector_export(const void * v, const void * p_context, const char * header_file_name, const char * footer_file_name, FILE * fo);


/*-------------------Sorter------------------------*/
status_t ADT_Vector_sort(ADT_Vector_t * v);


/*-------------------Setters------------------------*/
status_t ADT_Vector_set_destructor (ADT_Vector_t * v, destructor_t pf);
status_t ADT_Vector_set_exporter(ADT_Vector_t * v, exporter_t pf);
status_t ADT_Vector_set_comparator(ADT_Vector_t * v, comparator_t pf);


#endif
