#include "parser.h"
#include "status.h"
#include "file_loader.h"



int main() {

    Filestring file_string;
    Status read_status = read_file("./test.c", &file_string);
    if (read_status != NO_ERROR) {
        status_print(read_status);
        return -1;
    }

    parser_start(&file_string);

}
