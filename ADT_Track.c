#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ADT_Track.h"
#include "mp3.h"
#include "types.h"


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

	/*Habría que validar que los parametros cumplen con el ancho del estandar, ya que cuando se crea el track se asigna memoria para eso.*/

	strcpy((*ptr_track) -> name, name);
	strcpy((*ptr_track) -> artist, artist);
	strcpy((*ptr_track) -> album, album);
	strcpy((*ptr_track) -> comment, comment);
	(*ptr_track) -> year = year;
	(*ptr_track) -> genre = genre;

	return OK;
}

status_t ADT_Track_new_from_mp3_file(FILE * fi, ADT_Track_t * *ptr_track)
{
	status_t  st;
	char MP3_HEADER[MP3_HEADER_SIZE];

	if(fi == NULL || ptr_track == NULL)
		return ERROR_NULL_POINTER;

	if((st = ADT_Track_new(ptr_track)) != OK)
		return st;

	if((st = read_header_from_mp3(fi ,MP3_HEADER)) != OK)
	{
		ADT_Track_destroy(ptr_track);
		return st;
	}

	if((st = parse_header_to_track(MP3_HEADER, *ptr_track)) != OK)
	{
		ADT_Track_destroy(ptr_track);
		return st;
	}

	return OK;
}


/*-------------------Destructor---------------------*/
status_t ADT_Track_destroy(ADT_Track_t * *ptr_track)
{
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

	fprintf(fo, "%s%s\n%s%s\n%s%s\n%s%d\n%s%s\n%s%c\n", "Nombre: ", p -> name, "Artista: ", p -> artist,
	"Album: ", p -> album, "Año: ", p -> year, "Comentario: ", p -> comment, "Genero: ", p -> genre);

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
int ADT_Track_compare_by_name(void * ptr_track1, void * ptr_track2)
{
	ADT_Track_t * p1 = (ADT_Track_t *) ptr_track1;
	ADT_Track_t * p2 = (ADT_Track_t *) ptr_track2;

	return strcmp(p1 -> name, p2 -> name);
}

int ADT_Track_compare_by_artist(void * ptr_track1, void * ptr_track2)
{
	ADT_Track_t * p1 = (ADT_Track_t *) ptr_track1;
	ADT_Track_t * p2 = (ADT_Track_t *) ptr_track2;

	return strcmp(p1 -> artist, p2 -> artist);
}

int ADT_Track_compare_by_genre(void * ptr_track1, void * ptr_track2)
{
	/*Es posible que se quiera que la comparacion entre generos sea lexicografica.*/
	/*En tal caso habría que pasar al literal de genre y hacer strcmp.            */
	ADT_Track_t * p1 = (ADT_Track_t *) ptr_track1;
	ADT_Track_t * p2 = (ADT_Track_t *) ptr_track2;

	return p1 -> genre - p2 -> genre;
}
