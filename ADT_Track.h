/* ADT_Track.h */

#ifndef ADT_TRACK__H
#define ADT_TRACK__H

#include <stdio.h>
#include "types.h"

typedef struct {
	char * name;
	char * artist;
	char * album;
	unsigned short year;
	char * comment;
	unsigned char genre;
} ADT_Track_t;

/*-------------------Constructors-------------------*/
status_t ADT_Track_new(ADT_Track_t * *);
status_t ADT_Track_new_from_parameters(ADT_Track_t * * ptr_track, char * name, char * artist, char * album, unsigned short year, char * comment, unsigned char genre);
status_t ADT_Track_new_from_mp3_file(FILE *, ADT_Track_t * *);


/*-------------------Destructor---------------------*/
status_t ADT_Track_destroy(void * *);


/*-------------------Exporters----------------------*/
status_t ADT_Track_printer(void * ptr_track, FILE * fo);
status_t ADT_Track_export_as_xml (const void * pv, const void * p_context, FILE * fo);
status_t ADT_Track_export_as_csv (const void * pv, const void * p_context, FILE * fo);


/*-------------------Getters------------------------*/
/*Se debe liberar la memoria de las cadenas de --------*/ 
/*caracteres devueltas por los getters luego de su uso.*/
status_t ADT_Track_get_name(ADT_Track_t *, char **);
status_t ADT_Track_get_artist(ADT_Track_t *, char **);
status_t ADT_Track_get_album(ADT_Track_t *, char **);
status_t ADT_Track_get_year(ADT_Track_t *, unsigned short *);
status_t ADT_Track_get_comment(ADT_Track_t *, char **);
status_t ADT_Track_get_genre(ADT_Track_t *, unsigned char *);


/*-------------------Setters------------------------*/
status_t ADT_Track_set_name(ADT_Track_t *, const char *);
status_t ADT_Track_set_artist(ADT_Track_t *, const char *);
status_t ADT_Track_set_album(ADT_Track_t *, char *);
status_t ADT_Track_set_year(ADT_Track_t *, unsigned short );
status_t ADT_Track_set_comment(ADT_Track_t *, const char *);
status_t ADT_Track_set_genre(ADT_Track_t *, unsigned char);


/*-------------------Comparators--------------------*/
/*Estos son los que necesitamos para el tp pero para quede completo habría que hacer los otros*/
int ADT_Track_compare_by_name(void * ptr_track1, void * ptr_track2);
int ADT_Track_compare_by_artist(void * ptr_track1, void * ptr_track2);
int ADT_Track_compare_by_genre(void * ptr_track1, void * ptr_track2);



#endif
