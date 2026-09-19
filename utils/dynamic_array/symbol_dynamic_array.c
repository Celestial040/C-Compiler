#include "dynamic_array/symbol_dynamic_array.h"
#include "status.h"
#include "dynamic_array/string_dynamic_array.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

Status allocate_symbol_dynamic_array(SymbolDynamicArray *symbol_dynamic_array, StringDynamicArray *string_dynamic_array, size_t size_requested) {
    SymbolEntry *symbol_entries = (SymbolEntry *) malloc(sizeof(SymbolEntry) * size_requested);
    if (symbol_entries == NULL) {
        return ALLOCATION_ERROR;
    }

    symbol_dynamic_array->capacity = size_requested;
    symbol_dynamic_array->entries = symbol_entries;
    symbol_dynamic_array->count = 0;
    symbol_dynamic_array->string_dynamic_array = string_dynamic_array;

    return NO_ERROR;
}

Status reallocate_symbol_dynamic_array(SymbolDynamicArray *symbol_dynamic_array, size_t size_requested) {
    SymbolEntry *temp = realloc(symbol_dynamic_array->entries, sizeof(SymbolEntry) * size_requested);
    if (temp == NULL) {
        return ALLOCATION_ERROR;
    }

    symbol_dynamic_array->entries = temp;
    symbol_dynamic_array->capacity = size_requested;
    return NO_ERROR;
}

SymbolEntryPointer insert_symbol(SymbolDynamicArray *symbol_dynamic_array, const char *string, const size_t string_len, Semantic token_semantic) {
    SymbolEntryPointer return_pointer = {NO_ERROR, 0};
    StringDynamicArrayPointer string_pointer;

    if (symbol_dynamic_array->count + 1 >= symbol_dynamic_array->capacity) {
        Status reallocation_status = reallocate_symbol_dynamic_array(symbol_dynamic_array, symbol_dynamic_array->capacity*2);
        if (reallocation_status != NO_ERROR) {
            return_pointer.status = reallocation_status;
            return return_pointer;
        }
    }

    return_pointer.symbol_id = symbol_dynamic_array->count;
    string_pointer = insert_string(symbol_dynamic_array->string_dynamic_array, string, string_len);
    symbol_dynamic_array->entries[symbol_dynamic_array->count].string_index = string_pointer.string_start;
    symbol_dynamic_array->entries[symbol_dynamic_array->count].string_length = string_pointer.string_length;
    symbol_dynamic_array->entries[symbol_dynamic_array->count].semantic = token_semantic;

    symbol_dynamic_array->count++;

    return return_pointer;
}


Status free_symbol_dynamic_array(SymbolDynamicArray *symbol_dynamic_array) {
    if (symbol_dynamic_array->entries == NULL || symbol_dynamic_array->capacity == 0) {
        return NULL_POINTER;
    }

    free(symbol_dynamic_array->entries);
    free_string_dynamic_array(symbol_dynamic_array->string_dynamic_array);
    symbol_dynamic_array->entries = NULL;
    symbol_dynamic_array->string_dynamic_array = NULL;
    symbol_dynamic_array->capacity = 0;
    symbol_dynamic_array->count = 0;

    return NO_ERROR;
}

void print_token(Token token) {
    switch (token.token_type) {
        case TOKEN_KEYWORD:
            printf("TOKEN_KEYWORD\n");
            switch (token.sub_token_type) {
                case AUTO: printf("AUTO\n"); break;
                case BREAK: printf("BREAK\n"); break;
                case CASE: printf("CASE\n"); break;
                case CHAR: printf("CHAR\n"); break;
                case CONST: printf("CONST\n"); break;
                case CONTINUE: printf("CONTINUE\n"); break;
                case DEFAULT: printf("DEFAULT\n"); break;
                case DO: printf("DO\n"); break;
                case DOUBLE: printf("DOUBLE\n"); break;
                case ELSE: printf("ELSE\n"); break;
                case ENUM: printf("ENUM\n"); break;
                case EXTERN: printf("EXTERN\n"); break;
                case FLOAT: printf("FLOAT\n"); break;
                case FOR: printf("FOR\n"); break;
                case GOTO: printf("GOTO\n"); break;
                case IF: printf("IF\n"); break;
                case INT: printf("INT\n"); break;
                case LONG: printf("LONG\n"); break;
                case REGISTER: printf("REGISTER\n"); break;
                case RETURN: printf("RETURN\n"); break;
                case SHORT: printf("SHORT\n"); break;
                case SIGNED: printf("SIGNED\n"); break;
                case SIZEOF: printf("SIZEOF\n"); break;
                case STATIC: printf("STATIC\n"); break;
                case STRUCT: printf("STRUCT\n"); break;
                case SWITCH: printf("SWITCH\n"); break;
                case TYPEDEF: printf("TYPEDEF\n"); break;
                case UNION: printf("UNION\n"); break;
                case UNSIGNED: printf("UNSIGNED\n"); break;
                case VOID: printf("VOID\n"); break;
                case VOLATILE: printf("VOLATILE\n"); break;
                case WHILE: printf("WHILE\n"); break;
                default: printf("UNKNOWN\n"); break;
            }
            break;
        case TOKEN_OPERATOR:
            printf("TOKEN_OPERATOR\n");
            switch (token.sub_token_type) {
                case PLUS: printf("PLUS\n"); break;
                case MINUS: printf("MINUS\n"); break;
                case STAR: printf("STAR\n"); break;
                case SLASH: printf("SLASH\n"); break;
                case MOD: printf("MOD\n"); break;
                case INCREMENT: printf("INCREMENT\n"); break;
                case DECREMENT: printf("DECREMENT\n"); break;
                case ASSIGN: printf("ASSIGN\n"); break;
                case PLUS_ASSIGN: printf("PLUS_ASSIGN\n"); break;
                case MINUS_ASSIGN: printf("MINUS_ASSIGN\n"); break;
                case STAR_ASSIGN: printf("STAR_ASSIGN\n"); break;
                case SLASH_ASSIGN: printf("SLASH_ASSIGN\n"); break;
                case MOD_ASSIGN: printf("MOD_ASSIGN\n"); break;
                case AND_ASSIGN: printf("AND_ASSIGN\n"); break;
                case OR_ASSIGN: printf("OR_ASSIGN\n"); break;
                case XOR_ASSIGN: printf("XOR_ASSIGN\n"); break;
                case LEFT_SHIFT_ASSIGN: printf("LEFT_SHIFT_ASSIGN\n"); break;
                case RIGHT_SHIFT_ASSIGN: printf("RIGHT_SHIFT_ASSIGN\n"); break;
                case EQUAL: printf("EQUAL\n"); break;
                case NOT_EQUAL: printf("NOT_EQUAL\n"); break;
                case LESS_THAN: printf("LESS_THAN\n"); break;
                case MORE_THAN: printf("MORE_THAN\n"); break;
                case LESS_EQUAL: printf("LESS_EQUAL\n"); break;
                case MORE_EQUAL: printf("MORE_EQUAL\n"); break;
                case LOGICAL_AND: printf("LOGICAL_AND\n"); break;
                case LOGICAL_OR: printf("LOGICAL_OR\n"); break;
                case LOGICAL_NOT: printf("LOGICAL_NOT\n"); break;
                case BIT_AND: printf("BIT_AND\n"); break;
                case BIT_OR: printf("BIT_OR\n"); break;
                case BIT_XOR: printf("BIT_XOR\n"); break;
                case BIT_NOT: printf("BIT_NOT\n"); break;
                case LEFT_SHIFT: printf("LEFT_SHIFT\n"); break;
                case RIGHT_SHIFT: printf("RIGHT_SHIFT\n"); break;
                case ARROW: printf("ARROW\n"); break;
                case DOT: printf("DOT\n"); break;
                case QUESTION: printf("QUESTION\n"); break;
                case COMMA: printf("COMMA\n"); break;
                default: printf("UNKNOWN\n"); break;
            }
            break;
        case TOKEN_PUNCTUATION:
            printf("TOKEN_PUNCTUATION\n");
            switch (token.sub_token_type) {
                case OPEN_ROUND_BRACKET: printf("OPEN_ROUND_BRACKET\n"); break;
                case CLOSE_ROUND_BRACKET: printf("CLOSE_ROUND_BRACKET\n"); break;
                case OPEN_SQUARE_BRACKET: printf("OPEN_SQUARE_BRACKET\n"); break;
                case CLOSE_SQUARE_BRACKET: printf("CLOSE_SQUARE_BRACKET\n"); break;
                case OPEN_CURLY_BRACKET: printf("OPEN_CURLY_BRACKET\n"); break;
                case CLOSE_CURLY_BRACKET: printf("CLOSE_CURLY_BRACKET\n"); break;
                case SEMICOLON: printf("SEMICOLON\n"); break;
                case COLON: printf("COLON\n"); break;
                case ELLIPSIS: printf("ELLIPSIS\n"); break;
                case HASH: printf("HASH\n"); break;
                case DOUBLE_HASH: printf("DOUBLE_HASH\n"); break;
                default: printf("UNKNOWN\n"); break;
            }
            break;
        case TOKEN_IDENTIFIER:
            printf("TOKEN_IDENTIFIER\n");
            break;
        case TOKEN_LITERAL_INT:
            printf("TOKEN_LITERAL_INT\n");
            break;
        case TOKEN_LITERAL_FLOAT:
            printf("TOKEN_LITERAL_FLOAT\n");
            break;
        case TOKEN_LITERAL_STRING:
            printf("TOKEN_LITERAL_STRING\n");
            break;
        case TOKEN_EOF:
            printf("TOKEN_EOF\n");
            break;
        case TOKEN_UNKNOWN:
            printf("TOKEN_UNKNOWN\n");
            break;
        default:
            printf("UNKNOWN\n");
            break;
    }
}
