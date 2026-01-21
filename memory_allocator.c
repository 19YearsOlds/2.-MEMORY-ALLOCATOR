#include <stdio.h>
#include <stdlib.h> // For malloc() and free()

typedef struct MemoryBlock {
    size_t size;
    struct MemoryBlock *next;
    int free;
} MemoryBlock;

#define BLOCK_SIZE sizeof(MemoryBlock)

MemoryBlock *freeList = NULL;

void *my_malloc(size_t size) {
    MemoryBlock *block;

    if (size <= 0) {
        return NULL;
    }

    // First allocation
    block = (MemoryBlock *)malloc(size + BLOCK_SIZE);
    if (!block) {
        return NULL; // malloc failed
    }
    block->size = size;
    block->free = 0;
    block->next = freeList;
    freeList = block;

    return (void *)(block + 1); // Return pointer after metadata
}

void my_free(void *ptr) {
    if (!ptr) return;

    MemoryBlock *block = (MemoryBlock *)ptr - 1;
    block->free = 1;
}

int main() {
    printf("Custom malloc/free implementation\n");

    int *arr = (int *)my_malloc(5 * sizeof(int));

    if (!arr) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    for (int i = 0; i < 5; i++) {
        arr[i] = i + 1;
    }

    printf("Allocated array: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    my_free(arr);
    printf("Memory freed.\n");

    return 0;
}