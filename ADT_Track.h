/* ADT_Track.h */

#ifndef ADT_TRACK__H
#define ADT_TRACK__H

#include <stdio.h>
#include "types.h"

#define MP3_HEADER_SIZE		128


#define LEXEM_START_TAG     0
#define LEXEM_SPAN_TAG      3

#define LEXEM_START_TITLE   3
#define LEXEM_SPAN_TITLE   30

#define LEXEM_START_ARTIST 33
#define LEXEM_SPAN_ARTIST  30

#define LEXEM_START_ALBUM  63
#define LEXEM_SPAN_ALBUM   30

#define LEXEM_START_YEAR   93
#define LEXEM_SPAN_YEAR     4

#define LEXEM_START_COMMENT 97
#define LEXEM_SPAN_COMMENT  30

#define LEXEM_START_GENRE  127
#define LEXEM_SPAN_GENRE     1

typedef struct {
	char name[LEXEM_SPAN_TITLE];
	char artist[LEXEM_SPAN_ARTIST];
	char album[LEXEM_SPAN_ALBUM];
	unsigned short year;
	char comment[LEXEM_SPAN_COMMENT];
	unsigned char genre;
} ADT_Track_t;

/*-------------------Constructors-------------------*/
status_t ADT_Track_new(ADT_Track_t * *);
status_t ADT_Track_new_from_parameters(ADT_Track_t * * ptr_track, char * name, char * artist, char * album, unsigned short year, char * comment, char genre);
status_t ADT_Track_new_from_mp3_file(FILE *, ADT_Track_t * *);


/*-------------------Destructor---------------------*/
status_t ADT_Track_destroy(ADT_Track_t * *);


/*-------------------Exporters----------------------*/
status_t ADT_Track_printer(void * ptr_track, FILE * fo);


/*-------------------Getters------------------------*/
status_t ADT_Track_get_name(ADT_Track_t *, char *);
status_t ADT_Track_get_artist(ADT_Track_t *, char *);
status_t ADT_Track_get_album(ADT_Track_t *, char *);
status_t ADT_Track_get_year(ADT_Track_t *, unsigned short *);
status_t ADT_Track_get_comment(ADT_Track_t *, char *);
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
