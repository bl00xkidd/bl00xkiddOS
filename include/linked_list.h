#ifndef _LINKED_LIST_H
#define _LINKED_LIST_H

#include <stddef.h>

#define BUFFER_SIZE 1024

// Define the node structure for the linked list
typedef struct node {
    char buffer[BUFFER_SIZE]; // Buffer to store the command
    struct node *next;        // Pointer to the next node
} node_t;

// Function declarations
void insert_node(node_t **head, const char *buffer);
void delete_node(node_t **head, const char *buffer);
void print_list(node_t *head);
void free_list(node_t **head);

#endif // _LINKED_LIST_H