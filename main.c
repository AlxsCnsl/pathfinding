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

    Node* nd = nodes_array[0];
    int nbr_s = get_links_nbr_by_id(nd->id, argv[1]);
    printf("Size = %d\n",nbr_s );

    printf("test %d", nodes_array[1]->links[1]->id);
    
}