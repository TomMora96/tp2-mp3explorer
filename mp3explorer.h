/* mp3explorer.h */

#ifndef MP3_EXPLORER__H
#define MP3_EXPLORER__H

#include <stdio.h>

#include "types.h"
#include "ADT_Vector.h"
#include "config.h" 

status_t load_vector (ADT_Vector_t ** ptr_track_vector, config_t *config);

#endif
