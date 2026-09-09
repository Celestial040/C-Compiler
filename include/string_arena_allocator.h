#ifndef STRING_ARENA_ALLOCATOR
#define STRING_ARENA_ALLOCATOR

#include "status.h"
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


Status arena_allocator(StringArenaMemory *arena_memory, size_t size_requested);
StringArenaPointer insert_string_to_arena(StringArenaMemory *arena, const char *string, const size_t string_len);

#endif
