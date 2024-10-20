#include "library.h"


int main(int argc, char* argv[])
{
    Error error = get_file_error(argv[1]);
    if(error){
        return error;
    }
    
    FILE* file = fopen(argv[1], "r");
    display_nods_nbr(file);
    file = fopen(argv[1], "r");
    display_links_nbr(file);
    file = fopen(argv[1], "r");
    display_nod_star(file);
    file = fopen(argv[1], "r");
    display_nod_end(file);
}