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
    display_node_start(argv[1]);
    display_node_end(argv[1]);
    int a = get_node_id_by_index(argv[1], 2);
    printf("Get_node_id_by_index : %d\n", a);

    Node **nodes_array = init_node(argv[1]);
    get_node_by_id(nodes_array, 5);
}