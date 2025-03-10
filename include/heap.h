// heap.h
#ifndef HEAP_H
#define HEAP_H

#include <stdint.h>

#define HEAP_BLOCK_TABLE_ENTRY_FREE 0x00
#define HEAP_BLOCK_TABLE_ENTRY_TAKEN 0x01
#define HEAP_BLOCK_HAS_NEXT 0x80
#define HEAP_BLOCK_IS_FIRST 0x40

struct heap_table {
    uint8_t *entries;
    size_t total_entries;
};

struct heap {
    struct heap_table *table;
    void *start_addr;
};

extern struct heap kernel_heap;
extern struct heap_table kernel_heap_table;

#endif