
#include "status.h"
#include "string_pool.h"
#include "symbol_pool.h"
#include "tokens_hashmap.h"

Status seed_keyword(TokensHashMap *hashmap, SymbolPool *symbol_pool) {

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
        token_semantic.sub_token_type = i;
        symbol_insertion_status = insert_symbol(symbol_pool, keyword_strings[i], keyword_lengths[i], token_semantic);
        if (symbol_insertion_status.status != 0 ) {
            return symbol_insertion_status.status;
        }

        hashmap_insertion_status = insert_item(hashmap, keyword_strings[i], keyword_lengths[i], symbol_insertion_status.symbol_id);
        if (hashmap_insertion_status != 0) {
            return hashmap_insertion_status;
        }

    }

    return NO_ERROR;
}

Status seed_operator(TokensHashMap *hashmap, SymbolPool *symbol_pool) {

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
        token_semantic.sub_token_type = i;
        symbol_insertion_status = insert_symbol(symbol_pool, operator_strings[i], operator_lengths[i], token_semantic);
        if (symbol_insertion_status.status != 0 ) {
            return symbol_insertion_status.status;
        }

        hashmap_insertion_status = insert_item(hashmap, operator_strings[i], operator_lengths[i], symbol_insertion_status.symbol_id);
        if (hashmap_insertion_status != 0) {
            return hashmap_insertion_status;
        }

    }

    return NO_ERROR;
}

Status seed_punctuation(TokensHashMap *hashmap, SymbolPool *symbol_pool) {

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
        token_semantic.sub_token_type = i;
        symbol_insertion_status = insert_symbol(symbol_pool, punctuation_strings[i], punctuation_lengths[i], token_semantic);
        if (symbol_insertion_status.status != 0 ) {
            return symbol_insertion_status.status;
        }

        hashmap_insertion_status = insert_item(hashmap, punctuation_strings[i], punctuation_lengths[i], symbol_insertion_status.symbol_id);
        if (hashmap_insertion_status != 0) {
            return hashmap_insertion_status;
        }

    }

    return NO_ERROR;
}


Status setup_parser() {

    Status allocation_status;
    StringPool parser_string_pool;
    SymbolPool parser_symbol_pool;
    TokensHashMap parser_tokens_hashmap;

    allocation_status = allocate_string_pool(&parser_string_pool, 1024*10);
    if (allocation_status != NO_ERROR) {
        return allocation_status;
    }

    allocation_status = allocate_symbol_pool(&parser_symbol_pool, &parser_string_pool, 1024*2);
    if (allocation_status != NO_ERROR) {
        return allocation_status;
    }

    allocation_status = allocate_hashmap(&parser_tokens_hashmap, &parser_symbol_pool, 1024*2);
    if (allocation_status != NO_ERROR) {
        return allocation_status;
    }

    seed_keyword(&parser_tokens_hashmap, &parser_symbol_pool);
    seed_operator(&parser_tokens_hashmap, &parser_symbol_pool);
    seed_punctuation(&parser_tokens_hashmap, &parser_symbol_pool);

    return NO_ERROR;
}
