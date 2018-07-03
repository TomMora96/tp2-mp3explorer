/* xml.c */

#include <stdio.h>

#include "xml.h"

/* Este modulo contiene los detalles, definicion y 
ejecucion para manejar el formato de exportacion xml,
por ende, no es una biblioteca reutilizable para 
manejo de xml. */

char * xml_context[XML_CONTEXT_MAX_TAGS] = {
	XML_CONTEXT_TRACK_TAG, 
	XML_CONTEXT_NAME_TAG, 
	XML_CONTEXT_ARTIST_TAG, 
	XML_CONTEXT_GENRE_TAG
};
