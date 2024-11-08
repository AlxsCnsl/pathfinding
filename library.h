#ifndef LIBRARY_H
#define LIBRARY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "error_file.h"

typedef enum{ //Un booléen car c'est pratique
    FALSE,
    TRUE
} Bool;

typedef enum {
    START,
    NEUTRAL,
    END
} Role;

typedef struct n{
    int id;
    Role role;
    struct n **links;
    int links_size;
    int step;
    Bool mark;
} Node;

typedef struct {
    Node** items;
    Node* first_elem;
    Node* last_elem;
    int size;
    int step_index;
    int capacity;
} Queue;


int main(int argc, char* argv[]);

int str_debuts_str(char* str1, char* str2);

void display_nods_nbr(char *filename);
void display_links_nbr(char *filename);
void display_node_start(char *filename);
void display_node_end(char *filename);

int get_nods_nbr(char *filename);
int get_links_nbr(char *filename);
int get_node_start(char *filename);
int get_node_end(char *filename);

int get_node_id_by_index(char *filename, int index);
int get_links_nbr_by_id(int id, char* filename);
int get_oposit_id_in_file(int id, char* filename, int rank);

Node** init_node( char *filename );
void give_role(Node* node,char* filename);

Node* get_node_by_id(Node **nodes, int size, int id);

void display_nodes(Node* start);

Queue* init_queue(int capacity);

Bool is_empty_queue(Queue* queue);
Node* get_first_elem_queue(Queue* queue);
Node* get_last_elem_queue(Queue* queue);

void display_queue(Queue* queue);
void display_one_node(Node* node);

void enqueue(Queue* queue, Node* node);
Bool enqueue_links_node(Queue* queue, Node* node);
Bool enqueue_links_new_gen(Queue* queue, int *new_gen_index);
void dequeue(Queue* queue);

void mark_node(Node* node);
void unmark_node(Node* node);
void unmark_queue(Queue* queue);
Bool is_marked(Node* node);

Bool end_is_in_queue(Queue* queue);
Bool start_is_in_queue(Queue* queue);

void path_finder(Node* end, Node* start);
void display_path_finder(Node* start);

Node** get_unconnected_nodes( Node **nodes,int size ,Node *head);

//erreur trop specifique pour le error_file.c
int no_valid_path_error(Node* start);

#endif //LIBRARY_H