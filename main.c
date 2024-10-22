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
    Node **nodes_array = init_node(argv[1]);

    Node* nd = get_node_by_id(nodes_array, get_nods_nbr(argv[1]), 2);
    printf("id de nd : %d\n", nd->id);
    int nbr_s = get_links_nbr_by_id(nd->id, argv[1]);
    printf("Size = %d\n",nbr_s );
    int lol = get_oposit_id_in_file(4, argv[1], 3);
    printf("Oposit = %d", lol);
    
    //init_node(argv[1]);
}