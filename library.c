#include "library.h"

void display_nods_nbr(char *filename) //affiche le nombre de noeuds
{
    printf("nombre de noeud(s): %d\n", get_nods_nbr(filename));
}

void display_links_nbr(char *filename) //affiche le nombre de liens
{   
    printf("Nombre de lien(s): %d\n", get_links_nbr(filename));
}

void display_node_start(char *filename) //affiche le noeud de depart
{
    printf("start: %d\n", get_node_start(filename));
}

void display_node_end(char *filename) //affiche le noeud de fin
{
    printf("end: %d\n", get_node_end(filename));
}

int str_debuts_str(char* str1, char* str2) //verifie si str1 est dans str2() (pour le cross OS)
{
    int i;
    for(i = 0; i<strlen(str1); i++)
    {
        if(str1[i] != str2[i])
        {
            return 1;
        }
    }
    return 0;
}

int get_nods_nbr(char *filename)
{
    FILE* file = fopen(filename, "r");
    char buffer[256];
    int nods_nbr = 0;
    while(fgets(buffer, sizeof(buffer), file)!= NULL &&//while
    (str_debuts_str("#links", buffer)))//while
    {
        if(str_debuts_str("#", buffer)==1)
        {
            nods_nbr++;
        }
    }
    fclose(file);
    return nods_nbr;
}

int get_links_nbr(char *filename)
{
    FILE* file = fopen(filename, "r");
    char buffer[256];
    int links_nbr = 0;
    while (fgets(buffer, sizeof(buffer), file)!= NULL &&//while le while pour ignorer tout jusqu'a #links
    str_debuts_str("#links", buffer)){}//while
    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        links_nbr++;
    }
    return links_nbr;
}

int get_node_start(char *filename)
{
    FILE* file = fopen(filename, "r");
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)!= NULL &&//while  le while pour ignorer tout jusqu'a #start
    str_debuts_str("#start", buffer)){}//while 
    fgets(buffer, sizeof(buffer), file);
    fclose(file);
    return atoi(buffer);//transforme le char buffer en int 
}

int get_node_end(char *filename)
{
    FILE* file = fopen(filename, "r");
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)!= NULL && //while  le while pour ignorer tout jusqu'a #end
    str_debuts_str("#end", buffer)){} //while
    fgets(buffer, sizeof(buffer), file);
    fclose(file);
    return atoi(buffer);//transforme le char buffer en int 
}

int get_node_id_by_index(char *filename, int index){
    FILE* file = fopen(filename, "r");
    char buffer[256];
    int nods_id = 0;
    while(fgets(buffer, sizeof(buffer), file)!= NULL &&//while
    (str_debuts_str("#links", buffer)))//while
    {
        if(str_debuts_str("#", buffer)==1)
        {
            nods_id++;
            if(index == nods_id -1){
                return atoi(buffer);
            }
        }
    }
    return 0;
}

Node** init_node( char *filename ){
    int i, nodes_nbr = get_nods_nbr(filename);
    Node** n_tab = (Node**)malloc(nodes_nbr * sizeof(Node*));
    
    for(i=0;i<nodes_nbr;i++){
        n_tab[i] = (Node*)malloc(sizeof(Node));
        n_tab[i]->id = get_node_id_by_index(filename, i);
    }
    return n_tab;
}

Node* get_node_by_id(Node **nodes, int id)
{
    int i = 0;
    while (id != nodes[i]->id)
    {
        i++;
    }
    return nodes[i];
}

/*Node* init_graph(Node **nodes)
{

}*/