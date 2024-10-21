#include "library.h"

void display_nods_nbr(FILE *file) //affiche le nombre de noeuds
{
    char buffer[256];
    int nods_nbr = 0;
    while(fgets(buffer, sizeof(buffer), file)!= NULL &&//while
    (str_debuts_str("#links", buffer)))//while
    {
        if(str_debuts_str("#", buffer)==1)
        {
            nods_nbr++;
        }
    }
    printf("nombre de noeud(s): %d\n",nods_nbr);
}

void display_links_nbr(FILE *file) //affiche le nombre de liens
{   
    char buffer[256];
    int links_nbr = 0;
    while (fgets(buffer, sizeof(buffer), file)!= NULL &&//while le while pour ignorer tout jusqu'a #links
    str_debuts_str("#links", buffer)){}//while
    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        links_nbr++;
    }
    printf("Nombre de lien(s): %d\n", links_nbr);
}

void display_nod_star(FILE* file) //affiche le noeud de depart
{
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)!= NULL &&//while  le while pour ignorer tout jusqu'a #start
    str_debuts_str("#start", buffer)){}//while 
    fgets(buffer, sizeof(buffer), file);
    printf("start: %s", buffer);
}

void display_nod_end(FILE* file) //affiche le noeud de fin
{
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)!= NULL && //while  le while pour ignorer tout jusqu'a #end
    str_debuts_str("#end", buffer)){} //while
    fgets(buffer, sizeof(buffer), file);
    printf("end: %s", buffer);
}

int str_debuts_str(char* str1, char* str2) //verifie si str1 est dans str2() (pour le cross OS)
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
