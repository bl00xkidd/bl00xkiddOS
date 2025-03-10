#ifndef _SHELL_HISTORY_H
#define _SHELL_HISTORY_H

#include "linked_list.h" // Include the header where node_t is defined
#include "tty.h"
#include "memory.h"
#include "string.h"

#define BUFFER_SIZE 1024

// Define a new struct for shell history nodes
typedef struct history_node {
    char buffer[BUFFER_SIZE]; // Buffer to store the command
    struct history_node *next; // Pointer to the next node
} history_node_t;

// Function declarations for shell history
node_t *create_new_node(const char buffer[BUFFER_SIZE]);
void print_history(node_t *head);
void insert_at_head(node_t **head, node_t *node_to_insert);
#endif // _SHELL_HISTORY_H

