#ifndef PARSER_H
#define PARSER_H

#include "file_loader.h"
#include "status.h"
#include "string_arena_allocator.h"

Status parser_start(StringArenaMemory *string_arena, FileString *file_string);

#endif
