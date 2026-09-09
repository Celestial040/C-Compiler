#include "parser.h"
#include "status.h"
#include "file_loader.h"
#include "string_arena_allocator.h"


int main() {
    StringArenaMemory string_arena;
    Status arena_allocator_status = arena_allocator(&string_arena, 1024);
    if (arena_allocator_status != NO_ERROR) {
        status_print(arena_allocator_status);
        return 1;
    }

    FileString loaded_file_string;
    Status read_status = read_file("./test.c", &loaded_file_string);
    if (read_status != NO_ERROR) {
        status_print(read_status);
        return 1;
    }

    pass_string_arena(&string_arena);
    pass_loaded_file(&loaded_file_string);
    parser_start();

}
