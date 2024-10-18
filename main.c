#include "library.h"


int main(int argc, char **argv)
{
    FILE *file = NULL;
    file = fopen(argv[1], "r");

    if (file == NULL)
    {
        printf("Erreur : FILE_NOT_FOUND\n");
        return FILE_NOT_FOUND;
    }

    printf("Ouverture Réussie\n");

    display_links_nbr(file, 9);
}