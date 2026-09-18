#include "file_loader.h"
#include "new_parser.h"
#include "status.h"
#include <stddef.h>
#include <stdio.h>


Status runtime_exec() {

    Status status = NO_ERROR;
    FileString loaded_file_string;

    status = read_file("./target_files/test.c", &loaded_file_string);
    if (status != NO_ERROR) {
        return status;
    };

    status = setup_parser();
    if (status != NO_ERROR) {
        return status;
    };

    status = start_parser(&loaded_file_string);
    if (status != NO_ERROR) {
        return status;
    };

    return status;

}
