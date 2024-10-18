#include "library.h"


void display_nods_nbr(FILE *file)
{
    char buffer[256];
    int nods_nbr = 0;
    while(fgets(buffer, sizeof(buffer), file)!= NULL && (str_in_str("#links", buffer)))
    {
        if(str_in_str("#", buffer)==1)
        {
            nods_nbr++;
        }
    }
    printf("nombre de noeud(s): %d\n",nods_nbr);
}


void display_links_nbr(FILE *file)
{   
    char buffer[256];
    int links_nbr = 0;
    while (str_in_str("#links", buffer)!=0)
    {
        fgets(buffer, sizeof(buffer), file);
    }
    
    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        links_nbr++;
    }

    printf("Nombre de lien(s): %d\n", links_nbr);
}


int str_in_str(char* str1, char* str2) //verifie si str1 est dans str2() (pour le cross OS)
{
    int i;
    for(i = 0; i<strlen(str1); i++)
    {
        if(str1[i] != str2[i])
        {
            return 1;
        }
    }
    return 0;
}

