/* main.h */

#ifndef MAIN__H
#define MAIN__H

#include <stdio.h>
#include "types.h"
#include "config.h"

#define MIN_CMD_ARGS 7

#define CMD_ARG_OUTPUT_FORMAT_TOKEN_POS 1
#define CMD_ARG_OUTPUT_FORMAT_VALUE_POS 2
#define FORMAT_TOKEN "-fmt"

#define MAX_OUTPUT_FORMATS 2
#define OUTPUT_FORMAT_CSV_STR "csv"
#define OUTPUT_FORMAT_XML_STR "xml"

#define CMD_ARG_SORTING_CRITERION_TOKEN_POS 3
#define CMD_ARG_SORTING_CRTIERION_VALUE_POS 4
#define SORTING_CRIETERION_TOKEN "-sort"

#define MAX_SORTING_CRITERIA 3
#define SORT_BY_NAME_STR "name"
#define SORT_BY_ALBUM_STR "artist"
#define SORT_BY_GENRE_STR "genre"

#define CMD_ARG_OUTPUT_FILE_TOKEN_POS 5
#define CMD_ARG_OUTPUT_FILE_VALUE_POS 6
#define OUTPUT_FILE_TOKEN "-out"

status_t validate_arguments (int argc, char *argv[], config_t *config);

config_t config;

#endif
