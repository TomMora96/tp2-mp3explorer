#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mp3.h"
#include "ADT_Track.h"
#include "types.h"

status_t read_header_from_mp3(FILE * f, char * *header)
{
	size_t length;

	if(f == NULL || header == NULL)
		return ERROR_NULL_POINTER;

	fseek(f, 0, SEEK_END);						
    length = ftell(f);							
    fseek(f,length-MP3_HEADER_SIZE,SEEK_SET);	

    printf("%s\n", "antes fread");
    fflush(stdout);

    *header = (char *) malloc(MP3_HEADER_SIZE * sizeof(char));

    fread(*header,sizeof(char),MP3_HEADER_SIZE,f);

	printf("%s\n", "despues fread");
    fflush(stdout);

    return OK;
}

status_t parse_header_to_track(const char * header, ADT_Track_t *ptr_track)
{
	char buf[MP3_HEADER_SIZE];
	char * temp;

	if (header == NULL || ptr_track == NULL)
       return ERROR_NULL_POINTER;

    memcpy(buf,header+LEXEM_START_TITLE,LEXEM_SPAN_TITLE);
    buf[LEXEM_SPAN_TITLE] = '\0';
    ADT_Track_set_name(ptr_track, buf);
    fprintf(stdout, "%s%s\n", "acabo de salir de set_name. quedo copiado: ", ptr_track -> name);

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
    /*HARDCODEADO PA' PROBAR*/
    ADT_Track_set_genre(ptr_track, 'a');

    return OK;
}


status_t show_mp3_header (const char header[], FILE * fo)
{
    char buf[MP3_HEADER_SIZE];
    size_t len;

    if (header == NULL)
       return ERROR_NULL_POINTER;
    len = strlen(header);
    fprintf(fo, "%u\n", len);
    fprintf(fo, "%s\n", header);
    fprintf(fo, "%d\n", header[LEXEM_START_GENRE]);
    memcpy(buf,header+LEXEM_START_TAG,LEXEM_SPAN_TAG);
    buf[LEXEM_SPAN_TAG] = '\0';
    fprintf(fo,"%s%s\n","tag:",buf);

    memcpy(buf,header+LEXEM_START_TITLE,LEXEM_SPAN_TITLE);
    buf[LEXEM_SPAN_TITLE] = '\0';
    fprintf(fo,"%s%s\n","title:",buf);

    memcpy(buf,header+LEXEM_START_ARTIST,LEXEM_SPAN_ARTIST);
    buf[LEXEM_SPAN_ARTIST] = '\0';
    fprintf(fo,"%s%s\n","artist:",buf);

    memcpy(buf,header+LEXEM_START_ALBUM,LEXEM_SPAN_ALBUM);
    buf[LEXEM_SPAN_ALBUM] = '\0';
    fprintf(fo,"%s%s\n","album:",buf);

    memcpy(buf,header+LEXEM_START_YEAR,LEXEM_SPAN_YEAR);
    buf[LEXEM_SPAN_YEAR] = '\0';
    fprintf(fo,"%s%s\n","year:",buf);

    memcpy(buf,header+LEXEM_START_COMMENT,LEXEM_SPAN_COMMENT);
    buf[LEXEM_SPAN_COMMENT] = '\0';
    fprintf(fo,"%s%s\n","comment:",buf);

    memcpy(buf,header+LEXEM_START_GENRE,LEXEM_SPAN_GENRE);
    buf[LEXEM_SPAN_GENRE] = '\0';
    fprintf(fo,"%s%u\n","genre:",buf[0]);

    return OK;
}