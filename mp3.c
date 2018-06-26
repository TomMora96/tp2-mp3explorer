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

status_t parse_header_to_track(const char * header, ADT_Track_t *ptr_track)
{
	char buf[MP3_HEADER_SIZE];
	char * temp;

	if (header == NULL || ptr_track)
       return ERROR_NULL_POINTER;

    memcpy(buf,header+LEXEM_START_TITLE,LEXEM_SPAN_TITLE);
    buf[LEXEM_SPAN_TITLE] = '\0';
    ADT_Track_set_name(ptr_track, buf);

    memcpy(buf,header+LEXEM_START_ARTIST,LEXEM_SPAN_ARTIST);
    buf[LEXEM_SPAN_ARTIST] = '\0';
    ADT_Track_set_artist(ptr_track, buf);

    memcpy(buf,header+LEXEM_START_ALBUM,LEXEM_SPAN_ALBUM);
    buf[LEXEM_SPAN_ALBUM] = '\0';
    ADT_Track_set_album(ptr_track, buf);

    memcpy(buf,header+LEXEM_START_YEAR,LEXEM_SPAN_YEAR);
    buf[LEXEM_SPAN_YEAR] = '\0';
    ADT_Track_set_year(ptr_track, strtol(buf, &temp, 10));

    memcpy(buf,header+LEXEM_START_COMMENT,LEXEM_SPAN_COMMENT);
    buf[LEXEM_SPAN_COMMENT] = '\0';
    ADT_Track_set_comment(ptr_track, buf);

    memcpy(buf,header+LEXEM_START_GENRE,LEXEM_SPAN_GENRE);
    buf[LEXEM_SPAN_GENRE] = '\0';
    ADT_Track_set_genre(ptr_track, buf[0]);

    return OK;
}