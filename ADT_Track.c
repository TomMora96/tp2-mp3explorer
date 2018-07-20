/* ADT_Track.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ADT_Track.h"
/*#include "genres.h"*/
#include "mp3.h"
#include "types.h"
#include "xml.h"
#include "csv.h"


extern char * genres[];

/*-------------------Constructors-------------------*/
status_t ADT_Track_new(ADT_Track_t ** ptr_track)
{
	if(ptr_track == NULL)
		return ERROR_NULL_POINTER;

	if((*ptr_track = (ADT_Track_t *) malloc(sizeof(ADT_Track_t))) == NULL)
		return ERROR_OUT_OF_MEMORY;


	return OK;
}

status_t ADT_Track_new_from_parameters(ADT_Track_t ** ptr_track, const char * name, const char * artist, const char * album, unsigned short year, const char * comment, unsigned char genre)
{
	status_t st;

	if(ptr_track == NULL || name == NULL || artist == NULL || album == NULL || comment == NULL)
		return ERROR_NULL_POINTER;

	if((st = ADT_Track_new(ptr_track)) != OK)
		return st;

	if(strlen(name) > LEXEM_SPAN_TITLE)
	{
		ADT_Track_destroy((void **) ptr_track);
		return ERROR_INVALID_TRACK_PARAMETER;
	}
	strcpy((*ptr_track) -> name, name);

	if(strlen(artist) > LEXEM_SPAN_ARTIST)
	{
		ADT_Track_destroy((void **) ptr_track);
		return ERROR_INVALID_TRACK_PARAMETER;
	}
	strcpy((*ptr_track) -> artist, artist);

	if(strlen(album) > LEXEM_SPAN_ALBUM)
	{
		ADT_Track_destroy((void **) ptr_track);
		return ERROR_INVALID_TRACK_PARAMETER;
	}
	strcpy((*ptr_track) -> album, album);

	if(strlen(comment) > LEXEM_SPAN_COMMENT)
	{
		ADT_Track_destroy((void **) ptr_track);
		return ERROR_INVALID_TRACK_PARAMETER;
	}
	strcpy((*ptr_track) -> comment, comment);
	
	(*ptr_track) -> year = year;
	(*ptr_track) -> genre = genre;

	return OK;
}

status_t ADT_Track_new_from_mp3_file(FILE * fi, ADT_Track_t ** ptr_track)
{
	status_t  st;
	char mp3_header[MP3_HEADER_SIZE];
	char track_name[LEXEM_SPAN_TITLE];
	char track_artist[LEXEM_SPAN_ARTIST];
	char track_album[LEXEM_SPAN_ALBUM];
	unsigned short track_year;
	char track_comment[LEXEM_SPAN_COMMENT];
	unsigned char track_genre;

	if(fi == NULL || ptr_track == NULL)
		return ERROR_NULL_POINTER;

	if((st = get_mp3_header(fi, mp3_header)) != OK)
		return st;
	
	if((st = parse_mp3_header_to_parameters(mp3_header, &track_name, &track_artist, &track_album, &track_year, &track_comment, &track_genre)) != OK)
		return st;
	
	if((st = ADT_Track_new_from_parameters(ptr_track, track_name, track_artist, track_album, track_year, track_comment, track_genre)) != OK)
		return st;

	
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
status_t ADT_Track_print(void * ptr_track, FILE * fo)
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


	/*Si el genero del Track no se encuentra en el diccionario de generos*/
	/*exportar el numero asociado al genero.-----------------------------*/
	if(p -> genre > MAX_GENRES - 1)
		fprintf(fo, "%u", p -> genre);

	/*Si no, exportar el nombre del genero, que se encuentra en el dic de generos.*/
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

	fprintf(fo, "\t\t%c%s%c%s%s%s%c\n", '<', context[XML_CONTEXT_NAME_TAG_POS], '>', p -> name, "</", context[XML_CONTEXT_NAME_TAG_POS], '>');

	fprintf(fo, "\t\t%c%s%c%s%s%s%c\n", '<', context[XML_CONTEXT_ARTIST_TAG_POS], '>', p -> artist, "</", context[XML_CONTEXT_ARTIST_TAG_POS], '>');

	if(p-> genre > MAX_GENRES - 1)
		fprintf(fo, "\t\t%c%s%c%u%s%s%c\n", '<', context[XML_CONTEXT_GENRE_TAG_POS], '>', p -> genre, "</", context[XML_CONTEXT_GENRE_TAG_POS], '>');

	else
		fprintf(fo, "\t\t%c%s%c%s%s%s%c\n", '<', context[XML_CONTEXT_GENRE_TAG_POS], '>', genres[p -> genre], "</", context[XML_CONTEXT_GENRE_TAG_POS], '>');
	
	fprintf(fo, "\t%s%s%c\n", "</", context[XML_CONTEXT_TRACK_TAG_POS], '>');

	return OK;
}

status_t ADT_Track_export_as_html (const void * v, const void * p_context, FILE * fo)
{
	/*IMPLEMENTAR!*/
	return OK;
}

/*-------------------Getters------------------------*/
/*ADT_Track_get_name: Se debe liberar la memoria de la cadena de 
caracteres devuelta luego de su uso.*/
status_t ADT_Track_get_name(ADT_Track_t *track, char * *name)
{
	if(track == NULL || name == NULL)
		return ERROR_NULL_POINTER;

	if((*name = strdup(track -> name)) == NULL)
		return ERROR_OUT_OF_MEMORY;

	return OK;
}

/*ADT_Track_get_artist: Se debe liberar la memoria de la cadena de 
caracteres devuelta luego de su uso.*/
status_t ADT_Track_get_artist(ADT_Track_t *track, char * *artist)
{
	if(track == NULL || artist == NULL)
	return ERROR_NULL_POINTER;

	if((*artist = strdup(track -> artist)) == NULL)
		return ERROR_OUT_OF_MEMORY;

	return OK;
}

/*ADT_Track_get_album: Se debe liberar la memoria de la cadena de 
caracteres devuelta luego de su uso.*/
status_t ADT_Track_get_album(ADT_Track_t *track, char * *album)
{
	if(track == NULL || album == NULL)
		return ERROR_NULL_POINTER;

	if((*album = strdup(track -> album)) == NULL)
		return ERROR_OUT_OF_MEMORY;

	return OK;
}

/*ADT_Track_get_comment: Se debe liberar la memoria de la cadena de 
caracteres devuelta luego de su uso.*/
status_t ADT_Track_get_comment(ADT_Track_t *track, char * *comment)
{
	if(track == NULL || comment == NULL)
		return ERROR_NULL_POINTER;

	if((*comment = strdup(track -> comment)) == NULL)
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

/*El genero es de tipo unsigned char ya que el estandar ID3v1 la adjudica un byte al campo de genero.*/
status_t ADT_Track_get_genre(ADT_Track_t *track, unsigned char *genre)
{
	if(track == NULL || genre == NULL)
		return ERROR_NULL_POINTER;

	* genre = track -> genre;

	return OK;
}


/*-------------------Setters------------------------*/
/*Los setters realizan una copia del parametro------*/
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

status_t ADT_Track_set_comment(ADT_Track_t * ptr_track, const char * comment)
{
	if(ptr_track == NULL || comment == NULL)
		return ERROR_NULL_POINTER;

	strcpy(ptr_track -> comment, comment);
	return OK;	
}

status_t ADT_Track_set_year(ADT_Track_t * ptr_track, unsigned short year)
{
	if(ptr_track == NULL)
		return ERROR_NULL_POINTER;

	ptr_track -> year = year;

	return OK;	
}

/*El genero es de tipo unsigned char ya que el estandar ID3v1 la adjudica un byte al campo de genero.*/
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
