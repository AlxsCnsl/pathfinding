#ifndef LIBRARY_H
#define LIBRARY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "error_file.h"


typedef struct n{
    int id;
    struct n **links;
} Node;


int main(int argc, char* argv[]);


int str_debuts_str(char* str1, char* str2);
void display_nods_nbr(FILE *file);
void display_links_nbr(FILE *file);
void display_nod_star(FILE* file);
void display_nod_end(FILE* file);

#endif //LIBRARY_H