#include "status.h"
#include <string.h>
#include <stdlib.h>
#include <stddef.h>

typedef struct StringArenaNode {
    char *initial_pointer;
    size_t used;
    size_t capacity;
    struct StringArenaNode *prev;
}
StringArenaNode;

typedef struct StringArenaMemory {
    struct StringArenaNode *last_node;
}StringArenaMemory;

typedef struct StringArenaPointer {
    char *string_pointer;
    size_t string_length;
    Status status;
}StringArenaPointer;


Status new_arena_node(StringArenaNode **node, size_t size_requested) {
    StringArenaNode *new_node = (StringArenaNode *) malloc(sizeof(StringArenaNode));
    if (new_node == NULL) {
        return ALLOCATION_ERROR;
    }
    new_node->used = 0;
    new_node->capacity = size_requested;
    new_node->prev = NULL;
    new_node->initial_pointer = (char *) malloc(sizeof(char) * size_requested);
    if (new_node->initial_pointer == NULL) {
        free(new_node);
        return ALLOCATION_ERROR;
    }

    *node = new_node;
    return NO_ERROR;
}

Status arena_allocator(StringArenaMemory *arena_memory, size_t size_requested) {
    Status status = NO_ERROR;
    if (arena_memory->last_node == NULL) {
        StringArenaNode *new_node = NULL;
        status = new_arena_node(&new_node, size_requested);
        if (status != NO_ERROR ) {
            return status;
        }
        arena_memory->last_node = new_node;
    } else {
        StringArenaNode *new_node = NULL;
        status = new_arena_node(&new_node, size_requested);
        if (status != NO_ERROR ) {
            return status;
        }
        new_node->prev = arena_memory->last_node;
        arena_memory->last_node = new_node;
    }
    return status;
}



StringArenaPointer insert_string_to_arena(StringArenaMemory *arena, const char *string, const size_t string_len) {
    StringArenaPointer pointer_status = {.string_pointer = NULL, .string_length = 0, .status = NO_ERROR};

    if ((string_len + 1) >= (arena->last_node->capacity - arena->last_node->used)) {
        size_t new_node_size = arena->last_node->capacity * 2;
        if ((string_len + 1) >= new_node_size ) {
            new_node_size = (string_len + 1) * 2;
        }

        Status status = arena_allocator(arena, new_node_size);
        if (status != NO_ERROR) {
            pointer_status.status = status;
            return pointer_status;
        }
    }

    char *string_slot = arena->last_node->initial_pointer + arena->last_node->used;
    memcpy(string_slot,string,string_len);
    string_slot[string_len] = '\0';
    arena->last_node->used += (string_len+1);
    pointer_status.string_pointer = string_slot;
    pointer_status.string_length = string_len;

    return pointer_status;
}
