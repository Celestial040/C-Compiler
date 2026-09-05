#include "char_manip.h"
#include "file_loader.h"
#include "hashmap.h"
#include "status.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

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


static Filestring *current_file;
static size_t head = 0;
static size_t tail = 0;
static Hashmap *type_lookup_table;
static Hashmap *name_lookup_table;
static bool alphanum_state = false;

Status set_type_table(Hashmap *type_table) {
    if (type_table == NULL) {
        return NULL_POINTER;
    }

    type_lookup_table = type_table;
    return NO_ERROR;
}

Status set_name_table(Hashmap *name_table) {
    if (name_table == NULL) {
        return NULL_POINTER;
    }

    name_lookup_table = name_table;
    return NO_ERROR;
}

Status set_filestring_scan(Filestring *filestring){
    if (filestring == NULL) {
        return NULL_POINTER;
    }
    current_file = filestring;

    return NO_ERROR;
};

Identifier specific_case(const char current_char) {
    switch (current_char) {
        case ';':
            return (Identifier) {.type = SEMICOLON, .value = NULL, .value_length = 0};
            break;
        case '=':
            return (Identifier) {.type = ASSIGNMENT, .value = NULL, .value_length = 0};
            break;
        default:
            return (Identifier) {.type = UNKNOWN_IDENTIFIER, .value = NULL, .value_length = 0};
            break;
    }
}


Identifier scan() {

    while (head < current_file->length) {
        char *current_char = current_file->start + head;
        // printf("%ld \n",head);
        if (!is_alphabet_numeric(*current_char)) {
            if (alphanum_state) {
                alphanum_state = false;
                Status status = check_if_exist(type_lookup_table, current_file->start+tail, head - tail);

                if (status == NO_ERROR) {
                    return (Identifier) {.type = TYPE, .value=current_file->start+tail, head - tail};
                }

                status = check_if_exist(name_lookup_table, current_file->start+tail, head-tail);
                if (status == NO_ERROR) {
                    return (Identifier) {.type = NAME, .value=current_file->start+tail, head-tail};
                } else {
                    return (Identifier) {.type = NEW_NAME, .value=current_file->start+tail, head - tail};
                }
            }
            if (is_whitespace(*current_char)){
                head++;
                continue;
            } else {
                head++;
                return specific_case(*current_char);
            }
        }

        else {
            if (!alphanum_state) {
                alphanum_state = true;
                tail = head;
            }
            head++;
        }
    }
    return (Identifier) {.type = UNKNOWN_IDENTIFIER, .value = NULL, .value_length = 0};

}

void printheadtail() {
    printf("%ld , %ld \n", head, tail);
}
