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
    status = read_file("./test_files/test.c", &loaded_file_string);
    if (status != 0) goto error_exit;

    status = parser_start(&string_arena,&loaded_file_string);
    if (status != 0) goto error_exit;

    status_print(status);
    return status;

    error_exit:
    status_print(status);
    return status;

}
