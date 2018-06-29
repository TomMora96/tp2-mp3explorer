#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mp3.h"
#include "ADT_Track.h"
#include "types.h"

status_t read_header_from_mp3(FILE * f, char * header)
{
	size_t length;

	/*Validar!*/
	fseek(f, 0, SEEK_END);						
    length = ftell(f);							
    fseek(f,length-MP3_HEADER_SIZE,SEEK_SET);	

    fread(header,sizeof(char),MP3_HEADER_SIZE,f);

    return OK;
}
