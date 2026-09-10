#include "file_loader.h"
#include "flat_array_hashmap.h"
#include "status.h"
#include "string_arena_allocator.h"
#include <stddef.h>
#include <stdio.h>
#include "lexer.h"


StringArenaMemory *arena = NULL;
FileString *target_file = NULL;
TablesGroup tables_group;
Status status = 0;

void pass_string_arena(StringArenaMemory *string_arena) {
    arena = string_arena;
}

void pass_loaded_file(FileString *file_string) {
    target_file = file_string;
}

Status seed_keyword_table() {

    static const char *keyword_strings[] = {
        "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum",
        "extern", "float", "for", "goto", "if", "int", "long", "register", "return", "short", "signed",
        "sizeof", "static", "struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while", "inline", "_Bool",
    };

    static const size_t keyword_lengths[] = {
        4, 5, 4, 4, 5, 8, 7, 2, 6, 4, 4, 6, 5, 3, 4, 2, 3, 4, 8, 6, 5, 6, 6, 6, 6, 6, 7, 5, 8, 4, 8, 5, 6, 5,
    };

    for (size_t i = 0; i < 34; i++) {
        status = insert_item(&tables_group.keyword_table, keyword_strings[i], keyword_lengths[i]);
        if (status != 0) return status;
    }

    return NO_ERROR;
}
Status seed_operator_table() {

    static const char *operator_strings[] = {
        "+", "-", "*", "/", "%", "++", "--", "=", "+=", "-=", "*=", "/=", "%=", "&=", "|=", "^=", "<<=", ">>=",
        "==", "!=", "<", ">", "<=", ">=", "&&", "||", "!", "&", "|", "^", "~", "<<", ">>", "->", ".", "?",
    };

    static const size_t operator_lengths[] = {
        1, 1, 1, 1, 1, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 2, 2, 1, 1, 2, 2, 2, 2, 1, 1, 1, 1, 1, 2, 2, 2, 1, 1,
    };

    for (size_t i = 0; i < 36; i++) {
        status = insert_item(&tables_group.operator_table, operator_strings[i], operator_lengths[i]);
        if (status != 0) return status;
    }

    return NO_ERROR;
}
Status seed_punctuation_table() {

    static const char *punctuation_strings[] = {
        "(", ")", "[", "]", "{", "}", ",", ";", ":", "...", "#", "##",
    };

    static const size_t punctuation_lengths[] = {
        1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 2,
    };

    for (size_t i = 0; i < 12; i++) {
        status = insert_item(&tables_group.punctuation_table, punctuation_strings[i], punctuation_lengths[i]);
        if (status != 0) return status;
    }

    return NO_ERROR;
}

Status tables_init() {
    Status table_creation_status[3] = { seed_keyword_table(), seed_operator_table(), seed_punctuation_table()};
    for (size_t i = 0; i < 3; i++) if (table_creation_status[i] != 0) return table_creation_status[i];
    return NO_ERROR;
}


Status parser_start() {
    Status tables_status[4];

    tables_status[0] = create_hashmap(&tables_group.keyword_table, 34*2);
    tables_status[1] = create_hashmap(&tables_group.operator_table, 36*2);
    tables_status[2] = create_hashmap(&tables_group.punctuation_table, 12*2);
    tables_status[3] = create_hashmap(&tables_group.symbol_table, 2048*2);

    for(size_t i = 0; i < 4; i++) {
        if (tables_status[i] != NO_ERROR) {
            return tables_status[i];
        };
    }

    status = tables_init();
    if (status != 0) return status;



    status = set_filestring_to_scan(target_file);
    if (status != NO_ERROR) return status;

    // Identifier result;
    // result = scan();
    // printf("%d\n", result.type);

    // result = scan();
    // printf("%d\n", result.type);

    // result = scan();
    // printf("%d\n", result.type);

    // result = scan();
    // printf("%d\n", result.type);

    // result = scan();
    // printf("%d\n", result.type);


    return NO_ERROR;
}
