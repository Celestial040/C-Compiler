#include "parser.h"
#include "status.h"
#include "file_loader.h"
#include "string_arena_allocator.h"

int main() {
    Status status = 0;

    StringArenaMemory string_arena;
    status = arena_allocator(&string_arena, 1024);
    if (status != 0) goto error_exit;

    FileString loaded_file_string;
    status = read_file("./test.c", &loaded_file_string);
    if (status != 0) goto error_exit;

    pass_loaded_file(&loaded_file_string);
    pass_string_arena(&string_arena);

    status = parser_start();
    if (status != 0) goto error_exit;

    error_exit:
    status_print(status);
    return status;

}
