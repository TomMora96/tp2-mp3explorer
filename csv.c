/* csv.c */

#include <stdio.h>

#include "csv.h"

/* Este modulo contiene los detalles, definicion y 
ejecucion para manejar el formato de exportacion csv,
por ende, no es una biblioteca reutilizable para 
manejo de csv. */


/*Es necesario declarar una variable en vez de usar directamente usar la macro-----*/
/*porque las primitivas exportadoras reciven como agrumento del tipo puntero a void*/
/*a la dirección del contexto.-----------------------------------------------------*/
char csv_context = CSV_DELIMITER;

