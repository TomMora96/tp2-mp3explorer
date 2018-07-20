/* mp3explorer.h */

#ifndef MP3_EXPLORER__H
#define MP3_EXPLORER__H

#include <stdio.h>

#include "types.h"
#include "ADT_Vector.h"
#include "config.h" 

#define MAX_TRACK_EXPORTERS 3 
#define MAX_TRACK_COMPARATORS 3

status_t process_mp3_files(char * mp3_files_arr[], size_t arr_len, config_t *config, FILE * fo);

/*set_track_vector: Crea un ADT_Vector_t vacio y setea sus punteros a función según la configuración recivida por argumento.*/
/*Una vez utilizado el vector, debe llamarse a ADT_Vector_delete sobre el para liberar memoria.-----------------------------*/
status_t set_track_vector (ADT_Vector_t ** ptr_track_vector, config_t *config);
status_t load_mp3_tracks_from_files(char ** mp3_files_arr, size_t arr_len, ADT_Vector_t * ptr_track_vector);


#endif
