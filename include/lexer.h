#ifndef LEXER
#define LEXER

#include "file_loader.h"
#include "flat_array_hashmap.h"
#include "status.h"

typedef enum Identifier_Type {
    TYPE,
    NAME,
    NEW_NAME,
    ASSIGNMENT,
    SEMICOLON,
    ADD,
    SUB,
    DIV,
    MUL,
    STAR,
    POINT,
    ARROW,
    VALUE,
    IF_STATEMENT,
    ELSE_STATEMENT,
    ELSE_IF_STATEMENT,
    TYPEDEF,
    ENUM,
    STRUCT,
    LESS_THAN,
    MORE_THAN,
    EQUAL,
    RETURN,
    SINGLE_QUOTATION,
    DOUBLE_QUOTATION,
    OPEN_ROUND_BRACKET,
    CLOSE_ROUND_BRACKET,
    OPEN_SQUARE_BRACKET,
    CLOSE_SQUARE_BRACKET,
    OPEN_CURLY_BRACKET,
    CLOSE_CURLY_BRACKET,
    UNKNOWN_IDENTIFIER,
} Identifier_Type;

typedef struct Identifier {
    Identifier_Type type;
    char *value;
    size_t value_length;
}Identifier ;



Status set_type_table(HashMap *type_table);
Status set_symbol_table(HashMap *symbol_table);
Status set_filestring_to_scan(FileString *filestring);

Identifier scan();
void printheadtail();

#endif
