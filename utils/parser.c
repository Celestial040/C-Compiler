#include "file_loader.h"
#include "flat_array_hashmap.h"
#include "status.h"
#include "string_arena_allocator.h"
#include <stddef.h>
#include <stdio.h>
#include "lexer.h"

Status status;


StringArenaMemory *arena = NULL;
FileString *target_file = NULL;
HashMap type_table;
HashMap symbol_table;




void pass_string_arena(StringArenaMemory *string_arena) {
    arena = string_arena;

}

void pass_loaded_file(FileString *file_string) {
    target_file = file_string;
}

Status type_table_init() {

    char *primitive_type[6] = {"char", "short", "int", "long", "float", "double"};
    size_t primitive_type_length[6] = {4,5,3,4,5,6};
    StringArenaPointer primitive_type_string[6];

    static const char *keyword_strings[] = {
        "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum",
        "extern", "float", "for", "goto", "if", "int", "long", "register", "return", "short", "signed",
        "sizeof", "static", "struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while", "inline", "_Bool",
    };

    static const size_t keyword_lengths[] = {
        4, 5, 4, 4, 5, 8, 7, 2, 6, 4, 4, 6, 5, 3, 4, 2, 3, 4, 8, 6, 5, 6, 6, 6, 6, 6, 7, 5, 8, 4, 8, 5, 6, 5,
    };


    static const char *operator_strings[] = {
        "+", "-", "*", "/", "%", "++", "--", "=", "+=", "-=", "*=", "/=", "%=", "&=", "|=", "^=", "<<=", ">>=",
        "==", "!=", "<", ">", "<=", ">=", "&&", "||", "!", "&", "|", "^", "~", "<<", ">>", "->", ".", "?",
    };

    static const size_t operator_lengths[] = {
        1, 1, 1, 1, 1, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 2, 2, 1, 1, 2, 2, 2, 2, 1, 1, 1, 1, 1, 2, 2, 2, 1, 1,
    };

    static const char *punctuation_strings[] = {
        "(", ")", "[", "]", "{", "}", ",", ";", ":", "...", "#", "##",
    };

    static const size_t punctuation_lengths[] = {
        1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 2,
    };


    for (size_t i = 0; i<6; i++) {
        primitive_type_string[i] = insert_string_to_arena(arena, primitive_type[i], primitive_type_length[i]);
        if (primitive_type_string[i].status != NO_ERROR) {
            return primitive_type_string[i].status;
        }
    }

    for (size_t i = 0; i<6; i++) {
        insert_item(&type_table, primitive_type_string[i].string_pointer, primitive_type_string[i].string_length);
    }

    return NO_ERROR;
}


Status parser_start() {


    status = create_hashmap(&type_table, 12);
    if (status != NO_ERROR) {
        return status;
    };

    type_table_init();

    status = create_hashmap(&symbol_table, 2048);
    if (status != NO_ERROR) {
        return status;
    };



    status = set_type_table(&type_table);
    if (status != NO_ERROR) {
        return status;
    }
    status = set_symbol_table(&symbol_table);
    if (status != NO_ERROR) {
        return status;
    }

    status = set_filestring_to_scan(target_file);
    if (status != NO_ERROR) {
        return status;
    }

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
