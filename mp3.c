/* mp3.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mp3.h"
#include "types.h"

status_t get_mp3_header(FILE * f, char * header)
{
	size_t length;

	fseek(f, 0, SEEK_END);						
    length = ftell(f);							
    fseek(f,length-MP3_HEADER_SIZE,SEEK_SET);	

    fread(header,sizeof(char),MP3_HEADER_SIZE,f);

    return OK;
}
