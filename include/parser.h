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
} TablesGroup;


Status parser_start();
void pass_string_arena(StringArenaMemory *string_arena);
void pass_loaded_file(FileString *file_string);


#endif
