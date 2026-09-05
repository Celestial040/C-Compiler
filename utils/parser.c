#include "file_loader.h"
#include "hashmap.h"
#include "status.h"
#include "lexer.h"
#include <stddef.h>
#include <stdio.h>


Status type_table_init(Hashmap **hashmap) {
    Status status = create_hashmap(hashmap, 1024);
    if (status != NO_ERROR) {
        return status;
    }

    push_item(*hashmap, "int", 3);
    push_item(*hashmap, "char", 4);
    push_item(*hashmap, "float", 5);
    push_item(*hashmap, "double", 6);


    // status = check_if_exist(*hashmap, "int", 3);
    // status_print(status);
    // if (status != NO_ERROR) {
    //     status_print(status);
    //     return -1;
    // }


    return NO_ERROR;
}


Status parser_start(Filestring *filestring) {
    if (filestring == NULL || filestring->start == NULL) {
        return NULL_POINTER;
    }

    Hashmap *type_table;
    type_table_init(&type_table);


    Status status;
    status = set_type_table(type_table);
    if (status != NO_ERROR) {
        return status;
    }
    status = set_filestring_scan(filestring);
    if (status != NO_ERROR) {
        return status;
    }

    Identifier result;
    result = scan();
    printf("%d\n", result.type);

    result = scan();
    printf("%d\n", result.type);

    result = scan();
    printf("%d\n", result.type);

    result = scan();
    printf("%d\n", result.type);

    result = scan();
    printf("%d\n", result.type);


    return NO_ERROR;
}
