<<<<<<< Updated upstream
#include "library.h"

Error file_open(FILE *file, char *path, char *mode)
{
    file = fopen(path, mode);

    if (file == NULL)
    {
        printf("Erreur : FILE_NOT_FOUND\n");
        return FILE_NOT_FOUND;
    }

    printf("Ouverture Réussie\n");
    return 0;
}
=======
#include "library.h"
>>>>>>> Stashed changes
