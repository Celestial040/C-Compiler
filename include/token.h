#ifndef TOKEN_H
#define TOKEN_H

#include <stddef.h>

typedef enum TokenCategory {
    KEYWORD,
    OPERATOR,
    PUNCTUATION,
    IDENTIFIER,
    LITERAL,
} TokenCategory;

typedef enum Keyword {
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
    UNKNOWN_KEYWORD,
} Keyword;

typedef enum Operator {
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
    UNKNOWN_OPERATOR,
} Operator;

typedef enum Punctuation {
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
    UNKNOWN_PUNCTUATION,
} Punctuation;

typedef struct Token {
    TokenCategory category;
    union {
        Keyword keyword;
        Operator operator;
        Punctuation punctuation;
        struct {
            char *value;
            size_t value_length;
        } identifier;
        struct {
            char *value;
            size_t value_length;
        } literal;
    } data;
} Token;

#endif
