#include "error_file.h"

/*
FILE_NOT_FOUND : impossible d’ouvrir le fichier
NO_START_NODE : pas de nœud de début dans le fichier
NO_END_NODE : Pas de nœud de fin dans le fichier
NO_VALID_PATH : Le nœud de départ et de fin ne sont pas connecté
BAD_FILE_FORMAT : pas de section nodes ou links dans le fichier
*/

Error get_file_error(char* file_path_name)
{
    if(file_not_found_error(file_path_name))
    {
        return FILE_NOT_FOUND;
    }
    FILE* file = fopen(file_path_name, "r");
    if (no_start_node_error(file))
    {
        return NO_START_NODE;
    }
    file = fopen(file_path_name, "r");
    if (no_end_node_error(file))
    {
        return NO_END_NODE;
    }
    file = fopen(file_path_name, "r");
    if( bad_file_format_error(file)){
        return BAD_FILE_FORMAT;
    }
    return 0;
}


void display_file_error(Error error)
{
    switch(error)
    {
        case FILE_NOT_FOUND:
        printf("FILE_NOT_FOUND : impossible d’ouvrir le fichier\n");
        break;
        case NO_START_NODE:
        printf("NO_START_NODE : pas de nœud de début dans le fichier\n");
        break;
        case NO_END_NODE:
        printf("NO_END_NODE : Pas de nœud de fin dans le fichier\n");
        break;
        case NO_VALID_PATH:
        printf("NO_VALID_PATH : Le nœud de départ et de fin ne sont pas connecté\n");
        break;
        case BAD_FILE_FORMAT:
        printf("BAD_FILE_FORMAT : pas de section nodes ou links dans le fichier\n");
        break;
        default:
        printf("ERROR: erreur dans le fichier inconu\n");
    }
}


Error file_not_found_error(char* file_path_name)
{
    FILE* file = fopen(file_path_name, "r");
    if(file == NULL)
    {
        display_file_error(FILE_NOT_FOUND);
        return 1;
    }
    return 0;
}


Error no_start_node_error(FILE* file)
{
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)!= NULL )
    {
        if(str_debuts_str("#start", buffer)==0)//verifie si il y a #start
        {
            return 0;
        }
    }
    display_file_error(NO_START_NODE);
    return 1;
}


Error no_end_node_error(FILE* file)
{
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)!= NULL )
    {
        if(str_debuts_str("#end", buffer)==0)//verifie si il y a #end
        {
            return 0;
        }
    }
    display_file_error(NO_END_NODE);
    return 1;
}


Error bad_file_format_error(FILE* file){
    int nodes_yes = 0, links_yes = 0;
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)!= NULL )
    {
        if(str_debuts_str("#nodes", buffer)==0)//verifie si il y a #nodes
        {
             nodes_yes = 1;
        }
        if(str_debuts_str("#links", buffer)==0)//verifie si il y a #links
        {
             links_yes = 1;
        }
        if(nodes_yes == 1 && links_yes == 1)//si #links et #nodes, on return 0
        {
            return 0;
        }
    }
    display_file_error(BAD_FILE_FORMAT);
    return 1;
}