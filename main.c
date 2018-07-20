/* main.c */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "main.h"
#include "mp3explorer.h"
#include "types.h"
#include "errors.h"
#include "config.h"


/*Arreglo conteniendo las cadenas que el usuario puede ingresar para seleccionar--*/
/*el formato de salida. Las macros estan definidas en main.h----------------------*/
char *output_formats[MAX_OUTPUT_FORMATS] = {
	OUTPUT_FORMAT_CSV_STR,
	OUTPUT_FORMAT_XML_STR
};

/*Arreglo conteniendo las cadenas que el usuario puede ingresar para seleccionar--*/
/*el criterio de ordenamiento. Las macros estan definidas en main.h---------------*/
char *sort_criteria[MAX_SORTING_CRITERIA] = {
	SORT_BY_NAME_STR,
	SORT_BY_ALBUM_STR,
	SORT_BY_GENRE_STR
}; 


extern config_t config;

int main (int argc, char *argv[])
{
	status_t st;
	FILE * fo;

	if ((st = validate_arguments(argc, argv, &config)) != OK)
	{
		print_errors(st);
		return st;
	}

	if ((fo = fopen(config.output_file_name, "wt")) == NULL)
	{
		print_errors(ERROR_OUT_OF_DISK_SPACE);
		return ERROR_INPUT_FILE_NOT_FOUND;
	}

	/* argv + CMD_MIN_INPUT_ARGS: Arreglo de los nombres de los archivos mp3 */
	/* argc - CMD_MIN_INPUT_ARGS: Cantidad de archivos mp3 */
	if ((st = process_mp3_files(argv + MIN_CMD_ARGS, argc - MIN_CMD_ARGS, &config, fo)) != OK)
	{
		fclose(fo);
		print_errors(st);
		return st;
	}

	if (fclose(fo) == EOF)
	{
		print_errors(ERROR_OUT_OF_DISK_SPACE);
		return ERROR_OUT_OF_DISK_SPACE;
	}

	return OK;
}

/*Validación de argumentos:---------------------------------------------------------------------------------------*/
/*---La cantidad de argumentos ingresados debe alcanzar el valor minimo.------------------------------------------*/
/*---output format: La bandera de formato de salida debe ser la correcta y debe estar en la posición correcta.----*/
/*------------------El formato de salida ingresado debe estar definido.-------------------------------------------*/
/*---sorting criterion: La bandera de formato de salida debe ser la correcta y debe estar en la posición correcta.*/
/*----------------------El criterio de ordenamiento ingresado debe estar definido.--------------------------------*/
/*---output file: La bandera de formato de salida debe ser la correcta y debe estar en la posición correcta.------*/
/*----------------------------------------------------------------------------------------------------------------*/
status_t validate_arguments (int argc, char *argv[], config_t *config)
{	
	size_t i = 0;
	bool_t output_format_is_valid = FALSE;
	bool_t sort_criterion_is_valid = FALSE;

	if (argv == NULL || config == NULL)
		return ERROR_NULL_POINTER;

	/*Validación de la cantidad de argumentos.*/
	if (argc <= MIN_CMD_ARGS)
		return ERROR_PROGRAM_INVOCATION;

	
	/*Validación de las banderas y sus posiciones.*/
	if (strcmp(argv[CMD_ARG_OUTPUT_FORMAT_TOKEN_POS], FORMAT_TOKEN))
		return ERROR_PROGRAM_INVOCATION;

	if (strcmp(argv[CMD_ARG_SORTING_CRITERION_TOKEN_POS], SORTING_CRIETERION_TOKEN))
		return ERROR_PROGRAM_INVOCATION;

	if (strcmp(argv[CMD_ARG_OUTPUT_FILE_TOKEN_POS], OUTPUT_FILE_TOKEN))
		return ERROR_PROGRAM_INVOCATION;

	
	/*Validación del formato de salida ingresado.*/
	for(i = 0; i < MAX_OUTPUT_FORMATS && output_format_is_valid == FALSE; i++)
	{
		if(!strcmp(argv[CMD_ARG_OUTPUT_FORMAT_VALUE_POS], output_formats[i]))
		{
			config -> output_format = i;
			output_format_is_valid = TRUE;
		}
	}
	if(output_format_is_valid == FALSE)
		return ERROR_PROGRAM_INVOCATION;

	
	/*Validación del criterio de ordenamiento ingresado.*/
	for(i = 0; i < MAX_SORTING_CRITERIA && sort_criterion_is_valid == FALSE; i++)
	{
		if(!strcmp(argv[CMD_ARG_SORTING_CRTIERION_VALUE_POS], sort_criteria[i]))
		{
			config -> sort_criterion = i;
			sort_criterion_is_valid = TRUE;
		}
	}
	if(sort_criterion_is_valid == FALSE)
		return ERROR_PROGRAM_INVOCATION;

	
	config -> output_file_name = argv[CMD_ARG_OUTPUT_FILE_VALUE_POS];

	return OK;
}

