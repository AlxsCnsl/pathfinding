#include "library.h"


int main(int argc, char* argv[])
{
    Error error = get_file_error(argv[1]);
    if(error)
    {
        return error;
    } 
    display_nods_nbr(argv[1]);
    display_links_nbr(argv[1]);
    display_nod_star(argv[1]);
    display_nod_end(argv[1]);
}