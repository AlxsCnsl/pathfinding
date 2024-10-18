#include "library.h"


int display_nods_nbr(FILE *file)
{
    char buffer[256];
    int nods_nbr = 0;
    while(fgets(buffer, sizeof(buffer), file)!= NULL && (str_in_str("#links", buffer)))
    {
        if(str_in_str("#", buffer)==1)
        {
            nods_nbr++;
            printf("DEBUG(display): bufer %s\n", buffer);
        }
    }
    printf("nods = %d\n",nods_nbr);
    return nods_nbr;
}

int str_in_str(char* str1, char* str2) //verifie si str1 est dans str2() 
{
    int i;
    for(i = 0; i<strlen(str1); i++)
    {
        printf("DEBUG(str_in_str): str1[%d] %c /str2[%d] %c //POUR:%s\n",i, str1[i], i, str2[i], str1);
        if(str1[i] != str2[i])
        {
            printf("DEBUG(str_in_str): is diferent\n");
            return 1;
        }
    }
    printf("DEBUG(str_in_str): is identique\n");
    return 0;
}