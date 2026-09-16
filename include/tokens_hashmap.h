#ifndef TOKENS_HASHMAP_H
#define TOKENS_HASHMAP_H

#include "status.h"
#include "symbol_pool.h"
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

typedef uint8_t TokenType;
enum {
    TOKEN_KEYWORD,
    TOKEN_OPERATOR,
    TOKEN_PUNCTUATION,
    TOKEN_IDENTIFIER,
    TOKEN_LITERAL_INT,
    TOKEN_LITERAL_FLOAT,
    TOKEN_LITERAL_STRING,
    TOKEN_EOF
};

typedef uint8_t KeywordID ;
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
    WHILE,
    INLINE,
    BOOL,
    RESTRICT,
    COMPLEX,
    IMAGINARY,
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
};

typedef uint8_t PunctuationID;
enum {
    OPEN_ROUND_BRACKET,
    CLOSE_ROUND_BRACKET,
    OPEN_SQUARE_BRACKET,
    CLOSE_SQUARE_BRACKET,
    OPEN_CURLY_BRACKET,
    CLOSE_CURLY_BRACKET,
    COMMA,
    SEMICOLON,
    COLON,
    ELLIPSIS,
    HASH,
    DOUBLE_HASH,
};

typedef struct Token {
    size_t symbol_id;
    TokenType token_type;
    uint8_t sub_token_type;
    uint64_t line;
} Token;

typedef struct HashSlot {
    size_t symbol_id;
    uint32_t hash;
    uint32_t probe_count;
} HashSlot;



typedef struct TokensHashMap {
    HashSlot *slots;
    size_t capacity;
    size_t count;
    size_t mask;
    SymbolPool *symbol_pool;
} TokensHashMap;

Status init_hashmap(TokensHashMap *hashmap, size_t bucket_count);
Status insert_item(TokensHashMap *hashmap, const char *string, const size_t string_length, size_t symbol_id);

#endif
