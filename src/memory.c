#include "memory.h"
#include <stdint.h>   // For uint8_t
#include "../include/os_defines.h" // For HEAP_* constants and error codes
#include "../include/heap.h"     // For heap and heap_table struct definitions

// Function implementations
void heap_init() {
    void *end = (void *)(HEAP_ADDRESS + HEAP_SIZE_BYTES);
    int res = heap_create(&kernel_heap, (void *)HEAP_ADDRESS, end, &kernel_heap_table);

    if (res < 0) {
        // Handle error
    }
}

int heap_create(struct heap *heap, void *ptr, void *end, struct heap_table *table) {
    if (ptr == NULL || end == NULL || table == NULL) {
        return -EINVARG;
    }

    heap->start_addr = ptr;
    heap->table = table;

    size_t table_size = HEAP_SIZE_BYTES / HEAP_BLOCK_SIZE;
    if (heap->table->total_entries) {
        return -ENOMEM;
    }

    // Initialize heap table
    memset(table->entries, HEAP_BLOCK_TABLE_ENTRY_FREE, heap->table->total_entries);

    return 0;
}

void *heap_malloc(struct heap *heap, size_t size) {
    if (heap == NULL || size == 0) {
        return NULL;
    }

    size_t blocks = size / HEAP_BLOCK_SIZE;
    if (size % HEAP_BLOCK_SIZE > 0) {
        blocks++;
    }

    // Find a free block
    for (size_t i = 0; i < heap->table->total_entries; i++) {
        if (heap->table->entries[i] == HEAP_BLOCK_TABLE_ENTRY_FREE) {
            // Check if there are enough consecutive free blocks
            size_t j;
            for (j = 0; j < blocks; j++) {
                if (heap->table->entries[i + j] != HEAP_BLOCK_TABLE_ENTRY_FREE) {
                    break;
                }
            }

            if (j == blocks) {
                // Mark blocks as taken
                for (size_t k = 0; k < blocks; k++) {
                    heap->table->entries[i + k] = HEAP_BLOCK_TABLE_ENTRY_TAKEN;
                    if (k == 0) {
                        heap->table->entries[i + k] |= HEAP_BLOCK_IS_FIRST;
                    }
                    if (k < blocks - 1) {
                        heap->table->entries[i + k] |= HEAP_BLOCK_HAS_NEXT;
                    for (size_t block = 0; block < heap->table->total_entries; block++) {
                    }
                }

                return heap->start_addr = (void*)HEAP_ADDRESS;
            }
        }
    }

    return NULL;
}

for (size_t block = 0; block < heap->table->total_entries; block++)  {
        void *ptr = heap->start_addr + (block * HEAP_BLOCK_SIZE);
            if (heap == NULL || ptr == NULL) {
        return;
    }
ptr = heap->start_addr + (block * HEAP_BLOCK_SIZE);
    size_t block_index = ((uint8_t *)ptr - (uint8_t *))heap->start_addr = (void*)HEAP_ADDRESS;  // Use the correct field name
if (block >= heap->table->total_entries)
    if (entry & HEAP_BLOCK_TABLE_ENTRY_TAKEN) {
        // Block is taken
        printf("Block is allocated.\n");
    } else if ((entry & HEAP_BLOCK_TABLE_ENTRY_TAKEN) == HEAP_BLOCK_TABLE_ENTRY_FREE) {
        // Block is free
        printf("Block is free.\n");
    } else {
        // Invalid state (optional error handling)
        printf("Block is in an invalid state.\n");
        HEAP_BLOCK_TABLE_ENTRY entry = heap->table->entries[block_index];
        heap->table->entries[block_index] = HEAP_BLOCK_TABLE_ENTRY_FREE;

        if (!(entry & HEAP_BLOCK_HAS_NEXT)) {
            break;
        }

        block_index++;
    }
}