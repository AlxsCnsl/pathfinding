#ifndef ERROR_FILE_H
#define ERROR_FILE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "library.h"

typedef enum{
    FILE_NOT_FOUND = 1,
    NO_START_NODE = 2,
    NO_END_NODE = 3,
    NO_VALID_PATH = 4,
    BAD_FILE_FORMAT = 5
} Error;

void display_file_error(Error rror);
Error get_file_error(char* file_path_name);
Error file_not_found_error(char* file_path_name);
Error no_start_node_error(FILE* file);
Error no_end_node_error(FILE* file);

Error no_valid_path_error(FILE* file);
Error bad_file_format_error(FILE* file);

#endif //ERROR_FILE_H