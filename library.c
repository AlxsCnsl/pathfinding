#include "library.h"

void display_nods_nbr(char *filename) //Affiche le nombre de noeuds
{
    printf("nombre de noeud(s): %d\n", get_nods_nbr(filename));
}

void display_links_nbr(char *filename) //Affiche le nombre de liens
{   
    printf("Nombre de lien(s): %d\n", get_links_nbr(filename));
}

void display_node_start(char *filename) //Affiche le noeud de départ
{
    printf("start: %d\n", get_node_start(filename));
}

void display_node_end(char *filename) //Affiche le noeud de fin
{
    printf("end: %d\n", get_node_end(filename));
}

int str_debuts_str(char* str1, char* str2) //Vérifie si str1 est dans str2() (pour le cross OS)
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

int get_nods_nbr(char *filename) //Return le nombre de nodes
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

int get_links_nbr(char *filename) //Return le nombre de liens
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

int get_node_start(char *filename) //Return l'ID du node de depart
{
    FILE* file = fopen(filename, "r");
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)!= NULL &&//while  le while pour ignorer tout jusqu'a #start
    str_debuts_str("#start", buffer)){}//while 
    fgets(buffer, sizeof(buffer), file);
    fclose(file);
    return atoi(buffer);//transforme le char buffer en int 
}

int get_node_end(char *filename)//Return l'ID du node de fin
{
    FILE* file = fopen(filename, "r");
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)!= NULL && //while  le while pour ignorer tout jusqu'a #end
    str_debuts_str("#end", buffer)){} //while
    fgets(buffer, sizeof(buffer), file);
    fclose(file);
    return atoi(buffer);//transforme le char buffer en int 
}

int get_node_id_by_index(char *filename, int index)  //Retourne l'id en fonction de sa position dans le fichier
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

int get_links_nbr_by_id(int id, char* filename) //Return le nombre de liens d'un node
{
    FILE *file = fopen(filename, "r");
    char buffer[256];
    int i, left_id, right_id, links_nbr = get_links_nbr(filename);
    int return_value = 0;
    while (fgets(buffer, sizeof(buffer), file)!= NULL &&//while le while pour ignorer tout jusqu'a #links
    str_debuts_str("#links", buffer)){}//while
    for (i=1; i<=links_nbr; i++)
    {
        if(fgets(buffer, sizeof(buffer), file)!= NULL && //if//    on incremente le curseur de file et on aplique la ligne a bufer buffer 
        sscanf(buffer, "%d-%d", &left_id, &right_id) == 2) //if/   et on change les valeurs de  left_id et right_id
        {
            if(left_id == id || right_id == id)
            {
                return_value ++;
            }
        }
    }
    fclose(file); 
    return return_value;
}

int get_oposit_id_in_file(int id, char* filename, int rank)//ex: si id = 1 & rank =2 et que file =  1-2\n1-3 on a return 3
{                                                                                       //car c'est le 2e fois qu'on vois 1
    FILE *file = fopen(filename, "r");
    char buffer[256];
    int i, left_id, right_id, links_nbr = get_links_nbr(filename);
    int rank_lvl = 1;
    while (fgets(buffer, sizeof(buffer), file)!= NULL &&//while le while pour ignorer tout jusqu'a #links
    str_debuts_str("#links", buffer)){}//while
    for (i=0; i<=links_nbr; i++){
        if(fgets(buffer, sizeof(buffer), file)!= NULL && //if//    on incremente le curseur de file et on aplique la ligne a bufer buffer 
        sscanf(buffer, "%d-%d", &left_id, &right_id) == 2) //if/   et on change les valeurs de  left_id et right_id
        {
            if((left_id==id && right_id!=id)||(left_id!=id && right_id==id)) //un if pour regarder s'il y a id dans l'un des 2 cotés
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
    return 0;
}

void init_links_node(Node** tab_nodes, Node* node, char* filename) //Initie les liens d'un Node
{
    int i, id, size = get_links_nbr_by_id(node->id, filename);
    node->links = (Node**)malloc(size*sizeof(Node**));
    for(i = 0; i<size; i++)
    {
        id = get_oposit_id_in_file(node->id, filename, i+1);
        node->links[i] = get_node_by_id(tab_nodes, get_nods_nbr(filename), id);
    }
}

void init_links_node_by_node(Node** tab_nodes, char* filename )//Initie tous les liens de tous les noeuds
{
    int i, nodes_nbr = get_nods_nbr(filename);
    for(i=0;i<nodes_nbr;i++)
    {
        init_links_node(tab_nodes, tab_nodes[i], filename);
    }
}

Node** init_node( char *filename )//Initie les noeuds et leurs liens 
{
    int i, nodes_nbr = get_nods_nbr(filename);
    Node** n_tab = (Node**)malloc(nodes_nbr * sizeof(Node*));
    for(i=0;i<nodes_nbr;i++)
    {
        n_tab[i] = (Node*)malloc(sizeof(Node*));
        n_tab[i]->id = get_node_id_by_index(filename, i);
        n_tab[i]->step = 0;
        n_tab[i]->links_size = get_links_nbr_by_id(n_tab[i]->id, filename);
        n_tab[i]->mark = false;
        give_role(n_tab[i], filename);
    }
    init_links_node_by_node(n_tab, filename);
    return n_tab;
}

void give_role(Node* node, char* filename)//Donne le rôle type START END || NEUTRAL
{
    if(node->id == get_node_start(filename))
    {
        printf("ON A NOTRE NOTRE START <%d>\n", node->id);
        node->role = START;
    }
    else if(node->id == get_node_end(filename))
    {
        printf("ON A NOTRE END <%d>\n", node->id);
        node->role = END;
    }
    else
    {
        node->role = NEUTRAL;
    }
}

Node* get_node_by_id(Node **nodes, int size, int id) //Return un node grace à un ID
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


//les fonction à testé=================================================================================================les fonction à testé//


void display_nodes(Node* start)
{
    int new_gen_index = 0;
    Queue* queue= init_queue(100000);//grande taille pour la securité;
    enqueue(queue, start);
    while(enqueue_links_new_gen(queue, &new_gen_index)){}
    display_queue(queue);
    printf("queue size = %d\n", queue->size );
    unmark_queue(queue);
    free(queue);
}

bool enqueue_links_new_gen(Queue* queue, int *new_gen_index)
{
    queue->step_index ++;
    int i, next_gen_index = queue->size;
    bool return_value = false;
    for(i= *new_gen_index; i<next_gen_index; i++){
        if(enqueue_links_node(queue, queue->items[i])){
            return_value = true;
        }
    }
    *new_gen_index = next_gen_index;
    return return_value;
}

bool enqueue_links_node(Queue* queue, Node* node) //ici le bool de retourn nous permet de dire si il y a eu un ajout dans la file
{
    int i;
    bool return_value = false;
    for(i=0; i< node->links_size; i++){
        if(is_marked(node->links[i])==false){
            enqueue(queue, node->links[i]);
            return_value = true;
        }
    }
    return return_value;
}

Queue* init_queue(int capacity){
    int i;
    Queue* queue = malloc(sizeof(Queue));
    queue->items = NULL;
    queue->items = malloc(capacity*(sizeof(Node*)));
    queue->first_elem = NULL;
    queue->last_elem = NULL;
    queue->size = 0;
    queue->step_index = 1;
    queue->capacity = capacity;
    for(i=0; i<capacity; i++){
        queue->items[i] = NULL;
    }
    return queue;
}

bool is_ampty_queue(Queue* queue)
{
    if((queue->first_elem == NULL && queue->last_elem== NULL) ||queue->size==0)
    {
        return true;
    }
    return false;
}

Node* get_first_elem_queue(Queue* queue)
{
    if(is_ampty_queue(queue))
    {
        printf("ERREUR, first = NULL\n");
        exit(2);
    }
    return queue->first_elem;
}

Node* get_last_elem_queue(Queue* queue)
{
    if(is_ampty_queue(queue))
    {
        printf("ERREUR, last = NULL\n");
        exit(2);
    }
    return queue->last_elem;
}

void display_queue(Queue* queue)
{
    int i;
    if(is_ampty_queue(queue))
    {
        printf("La file est vidde\n");
        return;
    }
    for(i=0; i< queue->size; i++)
    {
        display_one_node(queue->items[i]);
    }
    printf("\n");
}

void display_one_node(Node* node)
{
    if(node == NULL)
    {
        printf("Tu essais de printf un node qui n'existe pas\n");
        return;
    }
    printf("%d ",node->id);
}

void enqueue(Queue* queue, Node* node)
{   
    printf("AH bah on passe dans le anqueue et on mark <%d>, ~%d~\n",node->id ,node->role);
    mark_node(node);
    node->step = queue->step_index;
    queue->items[queue->size] = node;
    queue->size ++;
    queue->last_elem = node;
    printf("on est aux step %d pour <%d>\n", node->step, node->id);
    if(queue->size==1)
    {
        queue->first_elem = node;
    }
}

void dequeue(Queue* queue)
{
    int i;
    if(is_ampty_queue(queue))
    {
        printf("La file est deja vide, rien à retiré\n");
        return;
    }
    for(i = 0; i< queue->size; i++){
        queue->items[i] = queue->items[i+1];
        queue->size --;
    }
}


void mark_node(Node* node)
{
    if(node->mark == false)
    {
        node->mark = true;
    }
}

void unmark_node(Node* node)
{
    if(node->mark == true)
    {
        node->mark = false;
        node->step = 0;
        printf("on demark <%d>\n",node->id);
    }
}

void unmark_queue(Queue* queue)
{
    int i;
    int size = queue->size;;
    for(i=0; i<size; i++)
    {
        unmark_node(queue->items[i]);
    }
}

bool is_marked(Node* node)
{
    if(node->mark == true)
    {
        return true;
    }
    return false;
}

bool end_is_in_queue(Queue* queue)
{
    int i;
    for(i=0; i<queue->size; i++)
    {
        if(queue->items[i]->role == END)
        {   
            return true;
        }
    }
    return false;
}

bool start_is_in_queue(Queue* queue)
{
    int i;
    for(i=0; i<queue->size; i++)
    {
        if(queue->items[i]->role == START)
        {
            return true;
        }
    }
    return false;
}


void path_finder(Node* end, Node* start)
{
    int new_gen_index = 0;
    Queue* queue= init_queue(100000);//grande taille pour la securité;
    enqueue(queue, end);
    while(enqueue_links_new_gen(queue, &new_gen_index)){}
    printf("++++==== step str %d// step end %d\n", start->step, end->step);
    display_path_finder(start);
    //unmark_queue(queue);
    //free(queue);
}

void display_path_finder(Node* start)
{
    Node* activ_node = start;
    int i, activ_step = activ_node->step;
    Node* test_node = NULL;
    int test_step;
    do
    {
        activ_step = activ_node->step;
        for(i=0; i<activ_node->links_size; i++)
        {
            test_node = activ_node->links[i];
            test_step = test_node->step;
            if(test_step < activ_step)
            {
                printf("%d ", activ_node->id);
                activ_node = test_node;
                activ_step = test_step;
            }
        }
    }while(activ_node->role != END);
    printf("%d\n", activ_node->id);
}

Node** get_unconnected_nodes( Node **nodes,int size ,Node *head)
{
    Node** return_nodes = (Node**)malloc(size*sizeof(Node*));
    int i, tab_index = 0;
    for(i = 0; i<size; i++)
    {
        if(nodes[i]->mark == false)
        {
            return_nodes[tab_index] = nodes[i];
            printf("Noeud non connecté : %d\n", return_nodes[tab_index]->id);
            tab_index ++;
        }
    }
    return return_nodes;
}

//N'est pas dans get_file_error pour sa complexité
int no_valid_path_error(Node* start) 
{
    int new_gen_index = 0;
    Queue* queue= init_queue(100000);//grande taille pour la securité;
    enqueue(queue, start);
    while(enqueue_links_new_gen(queue, &new_gen_index)){}
    if(end_is_in_queue(queue))
    {
        unmark_queue(queue);
        return 1;
    }
    unmark_queue(queue);
    display_file_error(NO_VALID_PATH);
    free(queue);
    return 0;
}

