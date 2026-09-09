#ifndef PARSER
#define PARSER
#include "file_loader.h"
#include "status.h"
#include "string_arena_allocator.h"

Status parser_start();
void pass_string_arena(StringArenaMemory *string_arena);
void pass_loaded_file(FileString *file_string);


#endif
