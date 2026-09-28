
#include "status.h"
#include "vector/string.h"
#include "vector/symbol.h"
#include "tokens_hashmap.h"
#include "lexer.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "parser.h"

static StringVector parser_string_vector;
static SymbolVector parser_symbol_vector;
static TokensHashMap parser_tokens_hashmap;

Status seed_keyword(void) {

    Status hashmap_insertion_status;
    SymbolEntryPointer symbol_insertion_status;
    Semantic token_semantic;

    const char *keyword_strings[32] = {
        "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum",
        "extern", "float", "for", "goto", "if", "int", "long", "register", "return", "short", "signed",
        "sizeof", "static", "struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while"
    };

    const size_t keyword_lengths[32] = {
        4, 5, 4, 4, 5, 8, 7, 2, 6, 4, 4, 6, 5, 3, 4, 2, 3, 4, 8, 6, 5, 6, 6, 6, 6, 6, 7, 5, 8, 4, 8, 5
    };

    size_t i;

    token_semantic.symbol_type = SYMBOL_KEYWORD;
    token_semantic.token_type = TOKEN_KEYWORD;

    for (i = 0; i < 32; i++) {
        token_semantic.sub_token_type = (uint8_t) i;

        symbol_insertion_status = insert_symbol(&parser_symbol_vector, keyword_strings[i], keyword_lengths[i], token_semantic);
        if (symbol_insertion_status.status != 0 ) {
            return symbol_insertion_status.status;
        }

        hashmap_insertion_status = insert_item(&parser_tokens_hashmap, keyword_strings[i], keyword_lengths[i], symbol_insertion_status.symbol_id);
        if (hashmap_insertion_status != 0) {
            return hashmap_insertion_status;
        }
    }

    return NO_ERROR;
}

Status seed_operator(void) {

    Status hashmap_insertion_status;
    SymbolEntryPointer symbol_insertion_status;
    Semantic token_semantic;


    const char *operator_strings[37] = {
        "+", "-", "*", "/", "%", "++", "--", "=", "+=", "-=", "*=", "/=", "%=", "&=", "|=", "^=", "<<=", ">>=",
        "==", "!=", "<", ">", "<=", ">=", "&&", "||", "!", "&", "|", "^", "~", "<<", ">>", "->", ".", "?", ","
    };

    const size_t operator_lengths[37] = {
        1, 1, 1, 1, 1, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 2, 2, 1, 1, 2, 2, 2, 2, 1, 1, 1, 1, 1, 2, 2, 2, 1, 1, 1
    };

    size_t i;

    token_semantic.symbol_type = SYMBOL_OPERATOR;
    token_semantic.token_type = TOKEN_OPERATOR;


    for (i = 0; i < 37; i++) {
        token_semantic.sub_token_type = (uint8_t) i;
        symbol_insertion_status = insert_symbol(&parser_symbol_vector, operator_strings[i], operator_lengths[i], token_semantic);
        if (symbol_insertion_status.status != 0 ) {
            return symbol_insertion_status.status;
        }

        hashmap_insertion_status = insert_item(&parser_tokens_hashmap, operator_strings[i], operator_lengths[i], symbol_insertion_status.symbol_id);
        if (hashmap_insertion_status != 0) {
            return hashmap_insertion_status;
        }

    }

    return NO_ERROR;
}

Status seed_punctuation(void) {

    Status hashmap_insertion_status;
    SymbolEntryPointer symbol_insertion_status;
    Semantic token_semantic;


    const char *punctuation_strings[11] = {
        "(", ")", "[", "]", "{", "}", ";", ":", "...", "#", "##",
    };

    const size_t punctuation_lengths[11] = {
        1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 2,
    };

    size_t i;

    token_semantic.symbol_type = SYMBOL_PUNCTUATION;
    token_semantic.token_type = TOKEN_PUNCTUATION;


    for (i = 0; i < 11; i++) {
        token_semantic.sub_token_type = (uint8_t) i;
        symbol_insertion_status = insert_symbol(&parser_symbol_vector, punctuation_strings[i], punctuation_lengths[i], token_semantic);
        if (symbol_insertion_status.status != 0 ) {
            return symbol_insertion_status.status;
        }

        hashmap_insertion_status = insert_item(&parser_tokens_hashmap, punctuation_strings[i], punctuation_lengths[i], symbol_insertion_status.symbol_id);
        if (hashmap_insertion_status != 0) {
            return hashmap_insertion_status;
        }

    }

    return NO_ERROR;
}


Status setup_parser(void) {

    Status allocation_status;

    allocation_status = allocate_string_vector(&parser_string_vector, 1024*10);
    if (allocation_status != NO_ERROR) {
        return allocation_status;
    }

    allocation_status = allocate_symbol_vector(&parser_symbol_vector, &parser_string_vector, 1024*2);
    if (allocation_status != NO_ERROR) {
        return allocation_status;
    }

    allocation_status = allocate_hashmap(&parser_tokens_hashmap, &parser_symbol_vector, 1024*2);
    if (allocation_status != NO_ERROR) {
        return allocation_status;
    }

    seed_keyword();
    seed_operator();
    seed_punctuation();

    return NO_ERROR;
}

Status start_parser(FileString *file_string) {
    Token token_recieved;
    size_t i;

    for (i = 0; i < 7; i++) {
        token_recieved = lexer_scan(&parser_tokens_hashmap, file_string);
        print_token(token_recieved);
    }

    return NO_ERROR;
}
