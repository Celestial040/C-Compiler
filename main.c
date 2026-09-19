#include "parser.h"
#include "status.h"
#include "file_loader.h"

int main() {
    Status status = NO_ERROR;
    FileString loaded_file_string;

    status = read_file("./target_files/test.c", &loaded_file_string);
    if (status != 0) goto error_exit;

    status = setup_parser();
    if (status != 0) goto error_exit;

    status = start_parser(&loaded_file_string);
    if (status != 0) goto error_exit;

    return status;

    status_print(status);
    return status;

    error_exit:
    status_print(status);
    return status;

}
