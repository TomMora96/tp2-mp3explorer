#include <stdio.h>
#include "ADT_Track.h"
#include "mp3.h"
#include "types.h"
#include "errors.h"

int main(void)
{
	status_t st;
	ADT_Track_t * ptr_track;
	FILE * f;

	printf("%s\n", "ENTRE AL PROGRAMA");
	fflush(stdout);

	if ((f = fopen("track.mp3","rb")) == NULL) {
     	fprintf(stderr,"%s\n","No se pudo abrir el archivo.");
        return 1;
    }
	if((st = ADT_Track_new_from_mp3_file(f, &ptr_track)) != OK)
	{
		errors_printer(st);
		return st;
	}

	if((st = ADT_Track_printer(ptr_track, stdout)) != OK)
	{
		errors_printer(st);
		return st;
	}

	return OK;

}