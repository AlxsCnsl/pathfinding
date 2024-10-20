#ifndef ERROR_FILE_H
#define ERROR_FILE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "error_file.h"

typedef enum{
    FILE_NOT_FOUND = 1,
    NO_START_NODE = 2,
    NO_END_NODE = 3,
    NO_VALIDE_PATH = 4,
    BAD_FILE_FORMAT = 5
} Error;

void display_file_errors(FILE* file);


#endif //ERROR_FILE_H