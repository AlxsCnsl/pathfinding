#include "library.h"


int main(int argc, char* argv[])
{
    FILE* file = fopen("test/test2.txt", "r");
    printf("ça passe\n");
    int b = display_nods_nbr(file);
}