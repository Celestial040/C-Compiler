#ifndef SYMBOL_POOL_H
#define SYMBOL_POOL_H

#include "status.h"
#include "string_pool.h"
#include <stddef.h>
#include <stdint.h>

typedef uint8_t TokenType;
enum {
    TOKEN_KEYWORD,
    TOKEN_OPERATOR,
    TOKEN_PUNCTUATION,
    TOKEN_IDENTIFIER,
    TOKEN_LITERAL_INT,
    TOKEN_LITERAL_FLOAT,
    TOKEN_LITERAL_STRING,
    TOKEN_EOF,
    TOKEN_UNKNOWN,
};

typedef uint8_t KeywordID;
enum {
    AUTO,
    BREAK,
    CASE,
    CHAR,
    CONST,
    CONTINUE,
    DEFAULT,
    DO,
    DOUBLE,
    ELSE,
    ENUM,
    EXTERN,
    FLOAT,
    FOR,
    GOTO,
    IF,
    INT,
    LONG,
    REGISTER,
    RETURN,
    SHORT,
    SIGNED,
    SIZEOF,
    STATIC,
    STRUCT,
    SWITCH,
    TYPEDEF,
    UNION,
    UNSIGNED,
    VOID,
    VOLATILE,
    WHILE
};

typedef uint8_t OperatorID;
enum {
    PLUS,
    MINUS,
    STAR,
    SLASH,
    MOD,
    INCREMENT,
    DECREMENT,
    ASSIGN,
    PLUS_ASSIGN,
    MINUS_ASSIGN,
    STAR_ASSIGN,
    SLASH_ASSIGN,
    MOD_ASSIGN,
    AND_ASSIGN,
    OR_ASSIGN,
    XOR_ASSIGN,
    LEFT_SHIFT_ASSIGN,
    RIGHT_SHIFT_ASSIGN,
    EQUAL,
    NOT_EQUAL,
    LESS_THAN,
    MORE_THAN,
    LESS_EQUAL,
    MORE_EQUAL,
    LOGICAL_AND,
    LOGICAL_OR,
    LOGICAL_NOT,
    BIT_AND,
    BIT_OR,
    BIT_XOR,
    BIT_NOT,
    LEFT_SHIFT,
    RIGHT_SHIFT,
    ARROW,
    DOT,
    QUESTION,
    COMMA,
};

typedef uint8_t PunctuationID;
enum {
    OPEN_ROUND_BRACKET,
    CLOSE_ROUND_BRACKET,
    OPEN_SQUARE_BRACKET,
    CLOSE_SQUARE_BRACKET,
    OPEN_CURLY_BRACKET,
    CLOSE_CURLY_BRACKET,
    SEMICOLON,
    COLON,
    ELLIPSIS,
    HASH,
    DOUBLE_HASH,
};


typedef uint8_t SymbolType;
enum {
    SYMBOL_NONE,
    SYMBOL_KEYWORD,
    SYMBOL_OPERATOR,
    SYMBOL_PUNCTUATION,
    SYMBOL_IDENTIFIER,
    SYMBOL_TYPEDEF_NAME,
    SYMBOL_VARIABLE,
    SYMBOL_FUNCTION,
    SYMBOL_STRUCT_TAG,
    SYMBOL_UNION_TAG,
    SYMBOL_ENUM_TAG,
    SYMBOL_ENUM_CONSTANT
};

typedef struct Token {
    size_t symbol_id;
    TokenType token_type;
    uint8_t sub_token_type;
    uint64_t line;
} Token;

typedef struct Semantic {
    TokenType token_type;
    uint8_t sub_token_type;
    SymbolType symbol_type;
}Semantic;

typedef struct SymbolEntry {
    size_t string_index;
    size_t string_length;
    size_t scope_depth;
    void *details;
    uint64_t added_attributes;
    Semantic semantic;
} SymbolEntry;

typedef struct SymbolPool {
    SymbolEntry *entries;
    size_t count;
    size_t capacity;
    StringPool *string_pool;
} SymbolPool;

typedef struct SymbolEntryPointer {
    size_t symbol_id;
    Status status;
} SymbolEntryPointer;

typedef struct TokenStatus {
    Token token;
    Status status;
}TokenStatus ;



Status allocate_symbol_pool(SymbolPool *symbol_pool, StringPool *string_pool, size_t size_requested);
SymbolEntryPointer insert_symbol(SymbolPool *symbol_pool, const char *string, const size_t string_len, Semantic token_semantic);
Status free_symbol_pool(SymbolPool *symbol_pool);

#endif
