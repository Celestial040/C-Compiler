#ifndef PARSER_H
#define PARSER_H

#include "file_loader.h"
#include "flat_array_hashmap.h"
#include "status.h"
#include "string_arena_allocator.h"

typedef struct TablesGroup {
    HashMap keyword_table;
    HashMap operator_table;
    HashMap punctuation_table;
    HashMap symbol_table;
    StringArenaMemory *string_arena;
} TablesGroup;


Status parser_start(StringArenaMemory *string_arena, FileString *file_string);


#endif
