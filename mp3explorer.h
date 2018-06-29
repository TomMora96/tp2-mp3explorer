/* mp3explorer.h */

#ifndef MP3_EXPLORER__H
#define MP3_EXPLORER__H

#include <stdio.h>

#include "types.h"
#include "ADT_Vector.h"
#include "config.h" 

status_t initialize_vector (ADT_Vector_t ** ptr_track_vector, config_t *config);
status_t load_mp3_tracks_from_files_to_vector(char ** mp3_files_arr, size_t arr_len, ADT_Vector_t ** ptr_track_vector);

#endif
