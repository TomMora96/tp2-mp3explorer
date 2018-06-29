/* xml.c */

#include <stdio.h>

#include "xml.h"

char * xml_context[XML_CONTEXT_MAX_TAGS] = {
	XML_CONTEXT_TRACK_TAG, 
	XML_CONTEXT_NAME_TAG, 
	XML_CONTEXT_ARTIST_TAG, 
	XML_CONTEXT_GENRE_TAG
};
