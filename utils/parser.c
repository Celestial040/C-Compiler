#include "parser.h"
#include "file_loader.h"
#include "flat_array_hashmap.h"
#include "status.h"
#include "string_arena_allocator.h"
#include <stddef.h>
#include <stdio.h>
#include "lexer.h"
#include "token.h"

Status seed_keyword_table(HashMap *keyword_table,StringArenaMemory *string_arena) {

    Status status;
    StringArenaPointer arena_pointer;

    static const char *keyword_strings[] = {
        "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum",
        "extern", "float", "for", "goto", "if", "int", "long", "register", "return", "short", "signed",
        "sizeof", "static", "struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while",
        "inline", "_Bool", "restrict", "_Complex", "_Imaginary",
    };

    static const size_t keyword_lengths[] = {
        4, 5, 4, 4, 5, 8, 7, 2, 6, 4, 4, 6, 5, 3, 4, 2, 3, 4, 8, 6, 5, 6, 6, 6, 6, 6, 7, 5, 8, 4, 8, 5,
        6, 5, 8, 8, 10,
    };

    for (size_t i = 0; i < 37; i++) {
        arena_pointer = insert_string_to_arena(string_arena, keyword_strings[i], keyword_lengths[i]);
        if (arena_pointer.status != NO_ERROR) {
            return status;
        }
        status = insert_item(keyword_table, arena_pointer.string_pointer, keyword_lengths[i],(Token) {.category = KEYWORD, .data.keyword = (Keyword) i});
        if (status != 0) return status;
    }

    return NO_ERROR;
}

Status seed_operator_table(HashMap *operator_table, StringArenaMemory *string_arena) {

    Status status;
    StringArenaPointer arena_pointer;

    static const char *operator_strings[] = {
        "+", "-", "*", "/", "%", "++", "--", "=", "+=", "-=", "*=", "/=", "%=", "&=", "|=", "^=", "<<=", ">>=",
        "==", "!=", "<", ">", "<=", ">=", "&&", "||", "!", "&", "|", "^", "~", "<<", ">>", "->", ".", "?",
    };

    static const size_t operator_lengths[] = {
        1, 1, 1, 1, 1, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 2, 2, 1, 1, 2, 2, 2, 2, 1, 1, 1, 1, 1, 2, 2, 2, 1, 1,
    };

    for (size_t i = 0; i < 36; i++) {
        arena_pointer = insert_string_to_arena(string_arena, operator_strings[i], operator_lengths[i]);
        if (arena_pointer.status != NO_ERROR) {
            return status;
        }
        status = insert_item(operator_table, arena_pointer.string_pointer, operator_lengths[i], (Token) {.category = OPERATOR, .data.operator = (Operator) i});
        if (status != 0) return status;
    }

    return NO_ERROR;
}

Status seed_punctuation_table(HashMap *punctuation_table, StringArenaMemory *string_arena) {

    Status status;
    StringArenaPointer arena_pointer;

    static const char *punctuation_strings[] = {
        "(", ")", "[", "]", "{", "}", ",", ";", ":", "...", "#", "##",
    };

    static const size_t punctuation_lengths[] = {
        1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 2,
    };

    for (size_t i = 0; i < 12; i++) {
        arena_pointer = insert_string_to_arena(string_arena, punctuation_strings[i], punctuation_lengths[i]);
        if (arena_pointer.status != NO_ERROR) {
            return status;
        }
        status = insert_item(punctuation_table, arena_pointer.string_pointer, punctuation_lengths[i], (Token) {.category = PUNCTUATION, .data.punctuation = (Punctuation) i});
        if (status != 0) return status;
    }

    return NO_ERROR;
}

Status tables_init(TablesGroup *tables_group) {
    Status table_creation_status[3] = { seed_keyword_table(&tables_group->keyword_table,tables_group->string_arena),
                                        seed_operator_table(&tables_group->operator_table,tables_group->string_arena),
                                        seed_punctuation_table(&tables_group->punctuation_table,tables_group->string_arena)};

    for (size_t i = 0; i < 3; i++) if (table_creation_status[i] != 0) return table_creation_status[i];
    return NO_ERROR;
}

Status parser_start(StringArenaMemory *string_arena, FileString *file_string) {
    TablesGroup tables_group;
    tables_group.string_arena = string_arena;
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

    Status status;
    status = tables_init(&tables_group);
    if (status != 0) return status;

    Token token = scan(&tables_group, file_string);
    print_token_detail(token);
    token = scan(&tables_group, file_string);
    print_token_detail(token);
    // token = scan(&tables_group, file_string);
    // print_token_detail(token);

    return NO_ERROR;
}
