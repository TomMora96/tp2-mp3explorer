/* mp3.h */

#ifndef MP3__H
#define MP3__H

#include <stdio.h>
#include <stdlib.h>
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

#define MAX_GENRES 127

status_t get_mp3_header(FILE * f, char * header);
status_t parse_mp3_header_to_parameters(const char * mp3_header, char (*name)[], char (*artist)[], char (*album)[], unsigned short *year, char (*comment)[], unsigned char *genre);

#endif
