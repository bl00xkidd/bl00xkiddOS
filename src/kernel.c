#ifndef _KERNEL_H
#define _KERNEL_H

#include <stdio.h>  // For snprintf
#include <stdlib.h> // For free
#include <string.h> // For strcpy, memset, strlen, strcmp
#include <ctype.h>  // For tolower

#include "../include/linked_list.h"
#include "../include/version.h"
#include "../include/tty.h"
#include "../include/io.h"
#include "../include/kbd.h"
#include "../include/string.h"
#include "../include/time.h"
#include "../include/math_shell.h"
#include "../include/parsing.h"
#include "../include/bool.h"
#include "../include/sha224.h"
#include "../include/sha256.h"
#include "../include/utils.h"
#include "../include/sleep.h"
#include "../include/thread.h"
#include "../include/memory.h"
#include "../include/shell_history.h"
#include "../include/calculator.h"
#include "../include/heap.h"

struct heap kernel_heap;
struct heap_table kernel_heap_table;
extern int default_font_color; // Explicitly declare as int

#define DEBUG false
#define BUFFER_SIZE 1024
#define MAX_VERSION_LENGTH 7

uint8_t numlock = true;
uint8_t capslock = false;
uint8_t scrolllock = false;
uint8_t shift = false;
char current_version[MAX_VERSION_LENGTH];

// Function declarations
void terminal_initialize(int font_color, int bg_color);
void terminal_set_colors(int font_color, int bg_color);
void print_logo();
void about(const char *version);
void print_prompt();
uint8_t scan();
void handle_keypress(uint8_t byte, char *buffer);
void execute_command(const char *buffer, const char *version, node_t *head);
node_t *create_new_node(const char *buffer);
void insert_at_head(node_t **head, node_t *new_node);

int main() {
    char buffer[BUFFER_SIZE] = {0}; // Input buffer
    char *lowered = NULL;           // Lowercase version of the buffer
    node_t *head = NULL;            // Linked list head
    uint8_t byte;                   // Scanned key

    // Initialize terminal
    terminal_initialize(default_font_color, COLOR_BLACK);
    terminal_set_colors(COLOR_BLUE, COLOR_BLACK);

    // Set the current version string
    if (snprintf(current_version, MAX_VERSION_LENGTH, "%u.%u.%u", V1, V2, V3 + 1) >= MAX_VERSION_LENGTH) {
        printk("\nError: Version string truncated");
        return 1;
    }

    // Print logo and welcome message
    print_logo();
    about(current_version);
    printk("\n\tType \"help\" for a list of commands.\n\n");
    printk("\n\tWelcome!\n\n");
    terminal_set_colors(default_font_color, COLOR_BLACK);

    // Initialize heap
    heap_init();

#ifdef DEBUG
    // Debugging memory allocation
    int *a = (int *)kmalloc(sizeof(int));
    void *b = kmalloc(5000);
    void *c = kmalloc(50000);

    if (a) {
        *a = 1;
        printk("\na: %d", *a);
        printk("\na: %p", (void *)a);
    } else {
        printk("\nkmalloc failed for a");
    }
    if (b) printk("\nb: %p", b);
    else printk("\nkmalloc failed for b");

    if (c) printk("\nc: %p", c);
    else printk("\nkmalloc failed for c");

    kfree(a);
    kfree(b);
    kfree(c);
#endif

    // Print the initial prompt
    print_prompt();

    // Main loop
    while (true) {
        while ((byte = scan()) != 0) {
            if (byte == ENTER) {
                // Convert buffer to lowercase
                lowered = string_tolower(buffer); // Use string_tolower instead of tolower
                if (lowered) {
                    strcpy(buffer, lowered);
                    free(lowered);
                }

                // Insert command into history
                if (head) insert_at_head(&head, create_new_node(buffer));

                // Execute command if buffer is not empty
                if (strlen(buffer) > 0) {
                    if (strcmp(buffer, "exit") == 0) {
                        printk("\nGoodbye!");
                        return 0;
                    }
                    execute_command(buffer, current_version, head);
                }

                // Print prompt and clear buffer
                print_prompt();
                memset(buffer, 0, BUFFER_SIZE);
                break;
            }

            // Handle keypress
            handle_keypress(byte, buffer);
        }
    }

    return 0;
}

node_t *create_new_node(const char *buffer) {
    node_t *new_node = (node_t *)kmalloc(sizeof(node_t));
    if (new_node) {
        strncpy(new_node->buffer, buffer, BUFFER_SIZE);
        new_node->next = NULL;
    }
    return new_node;
}

void insert_at_head(node_t **head, node_t *new_node) {
    if (new_node) {
        new_node->next = *head;
        *head = new_node;
    }
}

#endif  // _KERNEL_H