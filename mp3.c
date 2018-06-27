#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mp3.h"
#include "types.h"

status_t read_header_from_mp3(FILE * f, char (*header)[MP3_HEADER_SIZE])
{
	size_t length;

	if(f == NULL || header == NULL)
		return ERROR_NULL_POINTER;

	fseek(f, 0, SEEK_END);						
    length = ftell(f);							
    fseek(f,length-MP3_HEADER_SIZE,SEEK_SET);	

    fread(*header,sizeof(char),MP3_HEADER_SIZE,f);

    return OK;
}
