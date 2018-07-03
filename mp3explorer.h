/* mp3explorer.h */

#ifndef MP3_EXPLORER__H
#define MP3_EXPLORER__H

#include <stdio.h>

#include "types.h"
#include "ADT_Vector.h"
#include "config.h" 

#define MAX_VECTOR_EXPORTERS 2 
#define MAX_SORT_CRITERIA 3

char *sort_criteria[MAX_SORT_CRITERIA];
status_t process_init_vector (ADT_Vector_t ** ptr_track_vector, config_t *config);
status_t load_mp3_tracks_from_files(char ** mp3_files_arr, size_t arr_len, ADT_Vector_t * ptr_track_vector);
status_t process_mp3_files(char * argv[], int argc, ADT_Vector_t ** ptr_track_vector, FILE * fo);

#endif
