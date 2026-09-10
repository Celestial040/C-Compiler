#include "char_manip.h"
#include "file_loader.h"
#include "flat_array_hashmap.h"
#include "status.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include "parser.h"

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



// Identifier specific_case(const char current_char) {
//     switch (current_char) {
//         case ';':
//             return (Identifier) {.type = SEMICOLON, .value = NULL, .value_length = 0};
//             break;
//         case '=':
//             return (Identifier) {.type = ASSIGNMENT, .value = NULL, .value_length = 0};
//             break;
//         default:
//             return (Identifier) {.type = UNKNOWN_IDENTIFIER, .value = NULL, .value_length = 0};
//             break;
//     }
// }

static FileString *current_file;
static size_t head = 0;
static size_t tail = 0;
static TablesGroup *tables;
static bool alphanum_state = false;

void set_working_tables(TablesGroup *type_tables) {
    tables = type_tables;
}

Status set_filestring_to_scan(FileString *filestring){
    if (filestring == NULL) {
        return NULL_POINTER;
    }
    current_file = filestring;

    return NO_ERROR;
};



// Identifier scan() {

//     while (head < current_file->length) {
//         char *current_char = current_file->start + head;
//         if (!is_alphabet_numeric(*current_char)) {
//             if (alphanum_state) {
//                 alphanum_state = false;
//                 Status status = check_item(type_lookup_table, current_file->start+tail, head - tail);

//                 if (status == NO_ERROR) {
//                     return (Identifier) {.type = TYPE, .value=current_file->start+tail, head - tail};
//                 }

//                 status = check_item(symbol_lookup_table, current_file->start+tail, head-tail);
//                 if (status == NO_ERROR) {
//                     return (Identifier) {.type = NAME, .value=current_file->start+tail, head-tail};
//                 }
//                 else {
//                     return (Identifier) {.type = NEW_NAME, .value=current_file->start+tail, head - tail};
//                 }
//             }
//             if (is_whitespace(*current_char)){
//                 head++;
//                 continue;
//             } else {
//                 head++;
//                 return specific_case(*current_char);
//             }
//         }
//         else {
//             if (!alphanum_state) {
//                 alphanum_state = true;
//                 tail = head;
//             }
//             head++;
//         }
//     }

//     return (Identifier) {.type = UNKNOWN_IDENTIFIER, .value = NULL, .value_length = 0};

// }
