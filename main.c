#include "library.h"


int main(int argc, char* argv[])
{
    FILE* file = fopen(argv[1], "r");
    display_nods_nbr(file);
    display_links_nbr(file);
}