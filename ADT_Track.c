#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ADT_Track.h"
#include "genres.h"
#include "mp3.h"
#include "types.h"
#include "xml.h"
#include "csv.h"

/*-------------------Constructors-------------------*/
status_t ADT_Track_new(ADT_Track_t ** ptr_track)
{
	if(ptr_track == NULL)
		return ERROR_NULL_POINTER;

	if((*ptr_track = (ADT_Track_t *) malloc(sizeof(ADT_Track_t))) == NULL)
		return ERROR_OUT_OF_MEMORY;

	return OK;
}

status_t ADT_Track_new_from_parameters(ADT_Track_t * *ptr_track, char * name, char * artist, char * album, unsigned short year, char * comment, unsigned char genre)
{
	status_t st;

	if(ptr_track == NULL || name == NULL || artist == NULL || album == NULL || comment == NULL)
		return ERROR_NULL_POINTER;

	if((st = ADT_Track_new(ptr_track)) != OK)
		return st;

	if(strlen(name) > LEXEM_SPAN_TITLE)
		return ERROR_INVALID_TRACK_PARAMETER;
	strcpy((*ptr_track) -> name, name);

	if(strlen(artist) > LEXEM_SPAN_ARTIST)
		return ERROR_INVALID_TRACK_PARAMETER;
	strcpy((*ptr_track) -> artist, artist);

	if(strlen(album) > LEXEM_SPAN_ALBUM)
		return ERROR_INVALID_TRACK_PARAMETER;
	strcpy((*ptr_track) -> album, album);

	if(strlen(comment) > LEXEM_SPAN_COMMENT)
		return ERROR_INVALID_TRACK_PARAMETER;
	strcpy((*ptr_track) -> comment, comment);
	
	(*ptr_track) -> year = year;
	(*ptr_track) -> genre = genre;

	return OK;
}

status_t ADT_Track_new_from_mp3_file(FILE * fi, ADT_Track_t ** ptr_track)
{
	status_t  st;
	char mp3_header[MP3_HEADER_SIZE];
	char buf[MP3_HEADER_SIZE];
	char * temp;

	if(fi == NULL || ptr_track == NULL)
		return ERROR_NULL_POINTER;

	if((st = ADT_Track_new(ptr_track)) != OK)
		return st;

	if((st = read_header_from_mp3(fi, mp3_header)) != OK)
	{
		ADT_Track_destroy((void **) &ptr_track);
		return st;
	}

	memcpy(buf, mp3_header + LEXEM_START_TITLE, LEXEM_SPAN_TITLE);
    buf[LEXEM_SPAN_TITLE] = '\0';
    ADT_Track_set_name(*ptr_track, buf);

    memcpy(buf, mp3_header + LEXEM_START_ARTIST, LEXEM_SPAN_ARTIST);
    buf[LEXEM_SPAN_ARTIST] = '\0';
    ADT_Track_set_artist(*ptr_track, buf);

    memcpy(buf, mp3_header + LEXEM_START_ALBUM, LEXEM_SPAN_ALBUM);
    buf[LEXEM_SPAN_ALBUM] = '\0';
    ADT_Track_set_album(*ptr_track, buf);

    memcpy(buf, mp3_header + LEXEM_START_YEAR, LEXEM_SPAN_YEAR);
    buf[LEXEM_SPAN_YEAR] = '\0';
    ADT_Track_set_year(*ptr_track, strtol(buf, &temp, 10));

    memcpy(buf, mp3_header + LEXEM_START_COMMENT, LEXEM_SPAN_COMMENT);
    buf[LEXEM_SPAN_COMMENT] = '\0';
    ADT_Track_set_comment(*ptr_track, buf);

    memcpy(buf, mp3_header + LEXEM_START_GENRE, LEXEM_SPAN_GENRE);
    ADT_Track_set_genre(*ptr_track, buf[0]);


	return OK;
}


/*-------------------Destructor---------------------*/
status_t ADT_Track_destroy(void ** pp)
{	
	ADT_Track_t ** ptr_track = (ADT_Track_t **) pp;

	if(ptr_track == NULL)
		return ERROR_NULL_POINTER;
	
	free(*ptr_track);
	*ptr_track = NULL;

	return OK;
}


/*-------------------Exporters----------------------*/
status_t ADT_Track_printer(void * ptr_track, FILE * fo)
{
	ADT_Track_t * p = (ADT_Track_t *) ptr_track;

	fprintf(fo, "%s%s\n", "Title:", p -> name);
	fprintf(fo, "%s%s\n", "Artist:", p -> artist);
	fprintf(fo, "%s%s\n", "Album: ", p -> album);
	fprintf(fo, "%s%u\n", "Year:", p -> year);
	fprintf(fo, "%s%s\n", "Comment:", p -> comment);
	fprintf(fo, "%s%u\n", "Genre:", p -> genre);

	return OK;
}


status_t ADT_Track_export_as_csv (const void * pv, const void * p_context, FILE * fo)
{
	ADT_Track_t * p = (ADT_Track_t *) pv;
	char delimiter = *((char *)p_context);

	if (pv == NULL || p_context == NULL || fo == NULL)
		return ERROR_NULL_POINTER;

	
	fprintf(fo, "%s%c", p -> name, delimiter);

	fprintf(fo, "%s%c", p -> artist, delimiter);


	if(p-> genre > MAX_GENRES - 1)
		fprintf(fo, "%u", p -> genre);

	else
		fprintf(fo, "%s", genres[p -> genre]);
	
	fprintf(fo, "\n");


	return OK;
}

status_t ADT_Track_export_as_xml (const void * pv, const void * p_context, FILE * fo)
{
	ADT_Track_t *p = (ADT_Track_t *) pv;
	char * * context = (char * *) p_context;

	if (pv == NULL || p_context == NULL || fo == NULL)
		return ERROR_NULL_POINTER;

	fprintf(fo, "\t%c%s%c\n", '<', context[XML_CONTEXT_TRACK_TAG_POS], '>');

	fprintf(fo, "\t\t%c%s%c%s%c%c%s%c\n", '<', context[XML_CONTEXT_NAME_TAG_POS], '>', p -> name, '<', '\\',  context[XML_CONTEXT_NAME_TAG_POS], '>');

	fprintf(fo, "\t\t%c%s%c%s%c%c%s%c\n", '<', context[XML_CONTEXT_ARTIST_TAG_POS], '>', p -> artist, '<', '\\',  context[XML_CONTEXT_ARTIST_TAG_POS], '>');

	if(p-> genre > MAX_GENRES - 1)
		fprintf(fo, "\t\t%c%s%c%u%c%c%s%c\n", '<', context[XML_CONTEXT_GENRE_TAG_POS], '>', p -> genre, '<', '\\',  context[XML_CONTEXT_GENRE_TAG_POS], '>');

	else
		fprintf(fo, "\t\t%c%s%c%s%c%c%s%c\n", '<', context[XML_CONTEXT_GENRE_TAG_POS], '>', genres[p -> genre], '<', '\\',  context[XML_CONTEXT_GENRE_TAG_POS], '>');
	
	fprintf(fo, "\t%c%c%s%c\n", '<', '\\', context[XML_CONTEXT_TRACK_TAG_POS], '>');

	return OK;
}

/*-------------------Getters------------------------*/
status_t ADT_Track_get_name(ADT_Track_t *track, char * *name)
{
	if(track == NULL || name == NULL)
		return ERROR_NULL_POINTER;

	if((*name = strdup(track -> name)) == NULL)
		return ERROR_OUT_OF_MEMORY;

	return OK;
}

status_t ADT_Track_get_artist(ADT_Track_t *track, char * *artist)
{
	if(track == NULL || artist == NULL)
	return ERROR_NULL_POINTER;

	if((*artist = strdup(track -> artist)) == NULL)
		return ERROR_OUT_OF_MEMORY;

	return OK;
}

status_t ADT_Track_get_album(ADT_Track_t *track, char * *album)
{
	if(track == NULL || album == NULL)
		return ERROR_NULL_POINTER;

	if((*album = strdup(track -> album)) == NULL)
		return ERROR_OUT_OF_MEMORY;

	return OK;
}

status_t ADT_Track_get_year(ADT_Track_t *track, unsigned short *year)
{
	if(track == NULL || year == NULL)
		return ERROR_NULL_POINTER;

	*year = track -> year;

	return OK;
}

status_t ADT_Track_get_comment(ADT_Track_t *track, char * *comment)
{
	if(track == NULL || comment == NULL)
		return ERROR_NULL_POINTER;

	if((*comment = strdup(track -> comment)) == NULL)
		return ERROR_OUT_OF_MEMORY;

	return OK;
}

status_t ADT_Track_get_genre(ADT_Track_t *track, unsigned char *genre)
{
	if(track == NULL || genre == NULL)
		return ERROR_NULL_POINTER;

	*genre = track -> genre;

	return OK;
}


/*-------------------Setters------------------------*/
status_t ADT_Track_set_name(ADT_Track_t * ptr_track, const char * name)
{
	if(ptr_track == NULL || name == NULL)
		return ERROR_NULL_POINTER;

	strcpy(ptr_track -> name, name);
	return OK;	
}

status_t ADT_Track_set_artist(ADT_Track_t * ptr_track, const char * artist)
{
	if(ptr_track == NULL || artist == NULL)
		return ERROR_NULL_POINTER;

	strcpy(ptr_track -> artist, artist);
	return OK;	
}

status_t ADT_Track_set_album(ADT_Track_t * ptr_track, char * album)
{
	if(ptr_track == NULL || album == NULL)
		return ERROR_NULL_POINTER;

	strcpy(ptr_track -> album, album);
	return OK;	
}

status_t ADT_Track_set_year(ADT_Track_t * ptr_track, unsigned short year)
{
	if(ptr_track == NULL)
		return ERROR_NULL_POINTER;

	ptr_track -> year = year;
	return OK;	
}
status_t ADT_Track_set_comment(ADT_Track_t * ptr_track, const char * comment)
{
	if(ptr_track == NULL || comment == NULL)
		return ERROR_NULL_POINTER;

	strcpy(ptr_track -> comment, comment);
	return OK;	
}

status_t ADT_Track_set_genre(ADT_Track_t * ptr_track, unsigned char genre)
{
	if(ptr_track == NULL)
		return ERROR_NULL_POINTER;

	ptr_track -> genre = genre;
	return OK;	
}


/*-------------------Comparators--------------------*/
int ADT_Track_compare_by_name(const void * ptr_track1, const void * ptr_track2)
{
	ADT_Track_t ** p1 = (ADT_Track_t **) ptr_track1;
	ADT_Track_t ** p2 = (ADT_Track_t **) ptr_track2;

	return strcmp((*p1) -> name, (*p2) -> name);
}

int ADT_Track_compare_by_artist(const void * ptr_track1, const void * ptr_track2)
{
	ADT_Track_t * *p1 = (ADT_Track_t **) ptr_track1;
	ADT_Track_t * *p2 = (ADT_Track_t **) ptr_track2;

	return strcmp((*p1) -> artist, (*p2) -> artist);
}

int ADT_Track_compare_by_genre(const void * ptr_track1, const void * ptr_track2)
{
	ADT_Track_t ** p1 = (ADT_Track_t **) ptr_track1;
	ADT_Track_t ** p2 = (ADT_Track_t **) ptr_track2;

	return (*p1) -> genre - (*p2) -> genre;
}
