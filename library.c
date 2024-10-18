#include "library.h"

/******************************
*  Définitions des fonctions  *
******************************/

void display_links_nbr(FILE *file, int nodes_nbr)
{   
    char buffer[256];
    int links_nbr = 0, i = 0;
    /*for (i = 0 ; i < nodes_nbr + 4 ; i++)
    {
        fgets(buffer, sizeof(buffer), file);
    }*/

    while (strcmp(buffer, "#links\r\n"))
    {
        fgets(buffer, sizeof(buffer), file);
    }
    
    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        links_nbr++;
        printf("%s", buffer);
    }

    printf("Nombre de liens : %d\n", links_nbr);
}