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

status_t parse_mp3_header_to_parameters(const char * mp3_header, char (*name)[], char (*artist)[], char (*album)[], unsigned short *year, char (*comment)[], unsigned char *genre)
{
	char temp_name_str[LEXEM_SPAN_TITLE];
	char temp_artist_str[LEXEM_SPAN_ARTIST];
	char temp_album_str[LEXEM_SPAN_ALBUM];
	char temp_year_str[LEXEM_SPAN_YEAR];
	char temp_comment_str[LEXEM_SPAN_COMMENT];
	char temp_genre_str[LEXEM_SPAN_GENRE];
	char * temp_str;

	if(mp3_header == NULL || name == NULL || artist == NULL || album == NULL || year == NULL || comment == NULL || genre == NULL)
		return ERROR_NULL_POINTER;

	memcpy(temp_name_str, mp3_header + LEXEM_START_TITLE, LEXEM_SPAN_TITLE); 
    temp_name_str[LEXEM_SPAN_TITLE] = '\0';
    strcpy(*name, temp_name_str);

    memcpy(temp_artist_str, mp3_header + LEXEM_START_ARTIST, LEXEM_SPAN_ARTIST);
    temp_artist_str[LEXEM_SPAN_ARTIST] = '\0';
    strcpy(*artist, temp_artist_str);
   
    memcpy(temp_album_str, mp3_header + LEXEM_START_ALBUM, LEXEM_SPAN_ALBUM);
    temp_album_str[LEXEM_SPAN_ALBUM] = '\0';
    strcpy(*album, temp_album_str);

    memcpy(temp_year_str, mp3_header + LEXEM_START_YEAR, LEXEM_SPAN_YEAR);
    temp_year_str[LEXEM_SPAN_YEAR] = '\0';
    *year = strtol(temp_year_str, &temp_str, 10);

    if (*temp_str != '\0' && *temp_str != '\n')
    	return ERROR_PROGRAM_INVOCATION;

    memcpy(temp_comment_str, mp3_header + LEXEM_START_COMMENT, LEXEM_SPAN_COMMENT);
    temp_comment_str[LEXEM_SPAN_COMMENT] = '\0';
    strcpy(*comment, temp_comment_str);

    memcpy(temp_genre_str, mp3_header + LEXEM_START_GENRE, LEXEM_SPAN_GENRE);
    *genre = temp_genre_str[0];


    return OK;
}

char * genres[MAX_GENRES] = {
    "Blues",
    "Classic Rock",
    "Country",
    "Dance",
    "Disco",
    "Funk",
    "Grunge",
    "Hip-Hop",
    "Jazz",
    "Metal",
    "New Age",
    "Oldies",
    "Other",
    "Pop",
    "R&B",
    "Rap",
    "Reggae",
    "Rock",
    "Techno",
    "Industrial",
    "Alternative",
    "Ska",
    "Death Metal",
    "Pranks",
    "Soundtrack",
    "Euro-Techno",
    "Ambient",
    "Trip-Hop",
    "Vocal",
    "Jazz+Funk",
    "Fusion",
    "Trance",
    "Classical",
    "Instrumental",
    "Acid",
    "House",
    "Game",
    "Sound Clip",
    "Gospel",
    "Noise",
    "AlternRock",
    "Bass",
    "Soul",
    "Punk",
    "Space",
    "Meditative",
    "Instrumental Pop",
    "Instrumental Rock",
    "Ethnic",
    "Gothic",
    "Darkwave",
    "Techno-Industrial",
    "Electronic",
    "Pop-Folk",
    "Eurodance",
    "Dream",
    "Southern Rock",
    "Comedy",
    "Cult",
    "Gangsta",
    "Top 40",
    "Christian Rap",
    "Pop/Funk",
    "Jungle",
    "Native American",
    "Cabaret",
    "New Wave",
    "Psychadelic",
    "Rave",
    "Showtunes",
    "Trailer",
    "Lo-Fi",
    "Tribal",
    "Acid Punk",
    "Acid Jazz",
    "Polka",
    "Retro",
    "Musical",
    "Rock & Roll",
    "Hard Rock",
    "Folk",
    "Folk-Rock",
    "National Folk",
    "Swing",
    "Fast Fusion",
    "Bebob",
    "Latin",
    "Revival",
    "Celtic",
    "Bluegrass",
    "Avantgarde",
    "Gothic Rock",
    "Progressive Rock",
    "Psychedelic Rock",
    "Symphonic Rock",
    "Slow Rock",
    "Big Band",
    "Chorus",
    "Easy Listening",
    "Acoustic",
    "Humour",
    "Speech",
    "Chanson",
    "Opera",
    "Chamber Music",
    "Sonata",
    "Symphony",
    "Booty Brass",
    "Primus",
    "Porn Groove",
    "Satire",
    "Slow Jam",
    "Club",
    "Tango",
    "Samba",
    "Folklore",
    "Ballad",
    "Poweer Ballad",
    "Rhytmic Soul",
    "Freestyle",
    "Duet",
    "Punk Rock",
    "Drum Solo",
    "A Capela",
    "Euro-House",
    "Dance Hall"};
