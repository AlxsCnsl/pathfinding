#include "library.h"



int main(int argc, char* argv[])
{
    Error error = get_file_error(argv[1]);
    if(error)
    {
        return error;
    } 
    
    Node **nodes_array = init_node(argv[1]);
    int fst_id = get_node_start(argv[1]);
    int end_id = get_node_end(argv[1]);
    int size = get_nods_nbr(argv[1]);
    Node* fst_node = get_node_by_id(nodes_array, get_nods_nbr(argv[1]), fst_id);
    Node* end_node = get_node_by_id(nodes_array, get_nods_nbr(argv[1]), end_id);

    if(no_valid_path_error(fst_node)==0){
        return NO_VALID_PATH;
    }

    display_nods_nbr(argv[1]);
    display_links_nbr(argv[1]);
    display_node_start(argv[1]);
    display_node_end(argv[1]);
    
    path_finder(end_node, fst_node);

    get_unconnected_nodes(nodes_array, size, fst_node);

    //display_nodes(fst_node);
    
    return 0;
}