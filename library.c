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

int get_nods_nbr(char *filename) //get le nombre de nodes
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

int get_links_nbr(char *filename) // get le nombre de liens
{
    FILE* file = fopen(filename, "r");
    char buffer[256];
    int links_nbr = 0;
    while (fgets(buffer, sizeof(buffer), file)!= NULL &&//while le while pour ignorer tout jusqu'a #links
    str_debuts_str("#links", buffer)){}//while
    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        links_nbr ++;
    }
    return links_nbr;
}

int get_node_start(char *filename) // get le node de depart
{
    FILE* file = fopen(filename, "r");
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)!= NULL &&//while  le while pour ignorer tout jusqu'a #start
    str_debuts_str("#start", buffer)){}//while 
    fgets(buffer, sizeof(buffer), file);
    fclose(file);
    return atoi(buffer);//transforme le char buffer en int 
}

int get_node_end(char *filename)// get le node de fin
{
    FILE* file = fopen(filename, "r");
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)!= NULL && //while  le while pour ignorer tout jusqu'a #end
    str_debuts_str("#end", buffer)){} //while
    fgets(buffer, sizeof(buffer), file);
    fclose(file);
    return atoi(buffer);//transforme le char buffer en int 
}

int get_node_id_by_index(char *filename, int index)  // retourne l'id en fonction de ca position dans le fichier
{
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

int get_links_nbr_by_id(int id, char* filename) //retourne le nombre de lien qu'à un node
{
    FILE *file = fopen(filename, "r");
    char buffer[256];
    int i, left_id, right_id, links_nbr = get_links_nbr(filename);
    int retun_value = 0;
    while (fgets(buffer, sizeof(buffer), file)!= NULL &&//while le while pour ignorer tout jusqu'a #links
    str_debuts_str("#links", buffer)){}//while
    for (i=1; i<=links_nbr; i++)
    {
        if(fgets(buffer, sizeof(buffer), file)!= NULL && //if//    on incremente le curseur de file et on aplique la ligne a bufer buffer 
        sscanf(buffer, "%d-%d", &left_id, &right_id) == 2) //if/   et on change les valeurs de  left_id et right_id
        {
            if(left_id == id || right_id == id)
            {
                retun_value ++;
            }
        }
    }
    fclose(file); 
    return retun_value;
}

int get_oposit_id_in_file(int id, char* filename, int rank)//ex: si id = 1 & rank =2 et que fille =  1-2\n1-3 on a return 3; car c'est le 2e fois qu'on vois 1;
{
    FILE *file = fopen(filename, "r");
    char buffer[256];
    int i, left_id, right_id, links_nbr = get_links_nbr(filename);
    int rank_lvl = 1,retun_value = 0;
    while (fgets(buffer, sizeof(buffer), file)!= NULL &&//while le while pour ignorer tout jusqu'a #links
    str_debuts_str("#links", buffer)){}//while
    for (i=0; i<=links_nbr; i++){
        if(fgets(buffer, sizeof(buffer), file)!= NULL && //if//    on incremente le curseur de file et on aplique la ligne a bufer buffer 
        sscanf(buffer, "%d-%d", &left_id, &right_id) == 2) //if/   et on change les valeurs de  left_id et right_id
        {
            if((left_id==id && right_id!=id)||(left_id!=id && right_id==id)) //un if pour regarder si il y à id dans l'in des 2 coté 
            {        
                if(rank_lvl == rank)
                {
                    if(left_id == id && right_id != id)
                    {
                        return right_id;
                    }
                    return left_id;
                }
                rank_lvl ++;
            }
        }
    }
    fclose(file); 
    return 100;
}

void init_links_node(Node** tab_nodes, Node* node, char* filename) // initie les liens d'un Node  A finir =============================== ICI
{
    int i, id, size = get_links_nbr_by_id(node->id, filename);
    node->links = (Node**)malloc(size*sizeof(Node**));
    for(i = 0; i<size; i++)
    {
        id = get_oposit_id_in_file(node->id, filename, i+1);
        node->links[i] = get_node_by_id(tab_nodes, get_nods_nbr(filename), id);
    }
}

void init_links_node_by_node(Node** tab_nodes, char* filename )//initie tout les liens de tout les noeuds
{
    int i, nodes_nbr = get_nods_nbr(filename);
    for(i=0;i<nodes_nbr;i++)
    {
        init_links_node(tab_nodes, tab_nodes[i], filename);
    }
}

Node** init_node( char *filename )// initie les noeud et les lien 
{
    int i, nodes_nbr = get_nods_nbr(filename);
    Node** n_tab = (Node**)malloc(nodes_nbr * sizeof(Node*));
    
    for(i=0;i<nodes_nbr;i++)
    {
        n_tab[i] = (Node*)malloc(sizeof(Node*));
        n_tab[i]->id = get_node_id_by_index(filename, i);
    }
    init_links_node_by_node(n_tab, filename);
    return n_tab;
}

Node* get_node_by_id(Node **nodes, int size, int id) //recup un node grace à un id
{
    int i;
    for(i=0; i<size; i++)
    {
        if(id == nodes[i]->id)
        {
            return nodes[i];
        }
    }
    return NULL;
}
