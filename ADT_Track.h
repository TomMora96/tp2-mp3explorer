/* ADT_Track.h */

#ifndef ADT_TRACK__H
#define ADT_TRACK__H

#include <stdio.h>
#include "types.h"
#include "mp3.h"

typedef struct {
	char name[LEXEM_SPAN_TITLE + 1];
	char artist[LEXEM_SPAN_ARTIST + 1];
	char album[LEXEM_SPAN_ALBUM + 1];
	unsigned short year;
	char comment[LEXEM_SPAN_COMMENT + 1];
	unsigned char genre; /*El genero es de tipo unsigned char ya que el estandar ID3v1 la adjudica un byte al campo de genero.*/
} ADT_Track_t;

/*-------------------Constructors-------------------*/
status_t ADT_Track_new(ADT_Track_t * *);
status_t ADT_Track_new_from_parameters(ADT_Track_t ** ptr_track, const char * name, const char * artist, const char * album, unsigned short year, const char * comment, unsigned char genre);
status_t ADT_Track_new_from_mp3_file(FILE *, ADT_Track_t * *);


/*-------------------Destructor---------------------*/
status_t ADT_Track_destroy(void * *);


/*-------------------Exporters----------------------*/
status_t ADT_Track_print(void * ptr_track, FILE * fo);
status_t ADT_Track_export_as_xml (const void * pv, const void * p_context, FILE * fo);
status_t ADT_Track_export_as_csv (const void * pv, const void * p_context, FILE * fo);

/*NO IMPLEMENTADA*/
status_t ADT_Track_export_as_html (const void * v, const void * p_context, FILE * fo);



/*-------------------Getters------------------------*/
/*ADT_Track_get_name: Se debe liberar la memoria de la cadena de 
caracteres devuelta luego de su uso.*/
status_t ADT_Track_get_name(ADT_Track_t *, char **);

/*ADT_Track_get_artist: Se debe liberar la memoria de la cadena de 
caracteres devuelta luego de su uso.*/
status_t ADT_Track_get_artist(ADT_Track_t *, char **);

/*ADT_Track_get_albim: Se debe liberar la memoria de la cadena de 
caracteres devuelta luego de su uso.*/
status_t ADT_Track_get_album(ADT_Track_t *, char **);

status_t ADT_Track_get_year(ADT_Track_t *, unsigned short *);

/*ADT_Track_get_name: Se debe liberar la memoria de la cadena de 
caracteres devuelta luego de su uso.*/
status_t ADT_Track_get_comment(ADT_Track_t *, char **);

status_t ADT_Track_get_genre(ADT_Track_t *, unsigned char *);


/*-------------------Setters------------------------*/
/*Los setters realizan una copia del parametro------*/
status_t ADT_Track_set_name(ADT_Track_t *, const char *);
status_t ADT_Track_set_artist(ADT_Track_t *, const char *);
status_t ADT_Track_set_album(ADT_Track_t *, char *);
status_t ADT_Track_set_year(ADT_Track_t *, unsigned short );
status_t ADT_Track_set_comment(ADT_Track_t *, const char *);
status_t ADT_Track_set_genre(ADT_Track_t *, unsigned char);


/*-------------------Comparators--------------------*/
int ADT_Track_compare_by_name(const void * ptr_track1, const void * ptr_track2);
int ADT_Track_compare_by_artist(const void * ptr_track1, const void * ptr_track2);
int ADT_Track_compare_by_genre(const void * ptr_track1, const void * ptr_track2);



#endif
