#ifndef _MEMORY_H
#define _MEMORY_H 1

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#define EINVARG 2
#define ENOMEM 3

#define HEAP_BLOCK_TABLE_ENTRY_TAKEN 0x01
#define HEAP_BLOCK_TABLE_ENTRY_FREE 0x00

#define HEAP_BLOCK_HAS_NEXT 0b10000000
#define HEAP_BLOCK_IS_FIRST 0b01000000
#define HEAP_ADDRESS 0x01000000
#define HEAP_TABLE_ADRESS 0x00007E00

// 100 MB heap size
#define HEAP_SIZE_BYTES (1024 * 1024 * 100)

// 4 KB block size
#define HEAP_BLOCK_SIZE 4096

typedef unsigned char HEAP_BLOCK_TABLE_ENTRY;

struct heap_table {
    HEAP_BLOCK_TABLE_ENTRY *entries;
    size_t total;
};

struct heap {
    struct heap_table *table;
    void *saddr; // Start address of the heap data pool
};

// Declare kernel heap and heap table
extern struct heap kernel_heap;
extern struct heap_table kernel_heap_table;

// Function declarations
void heap_init();
int heap_create(struct heap *heap, void *ptr, void *end, struct heap_table *table);
void *heap_malloc(struct heap *heap, size_t size);
void heap_free(struct heap *heap, void *ptr);
void *kmalloc(size_t size);
void kfree(void *ptr);

#endif // _MEMORY_H