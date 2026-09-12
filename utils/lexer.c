#include "char_manip.h"
#include "file_loader.h"
#include "flat_array_hashmap.h"
#include "string_arena_allocator.h"
#include "token.h"
#include "status.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
// #include "parser.h"
#include "lexer.h"

typedef enum CharType {
    WHITESPACE,
    ALPHANUMERIC,
    SYMBOL,
    STRING_LITERAL,
    NUMERIC_LITERAL,
} CharType;

CharType char_type_check(const char target) {
    if (target == 39 || target == 34) {
        return STRING_LITERAL;
    } else if (is_alphabet_numeric(target)) {
        return ALPHANUMERIC;
    } else if (is_whitespace(target)) {
        return WHITESPACE;
    } else {
        return SYMBOL;
    }
}

Token scan(TablesGroup *working_table, FileString *file_string) {
    static size_t head = 0;
    static size_t tail = 0;
    static char *current_char = NULL;
    static CharType head_type = WHITESPACE;
    static CharType tail_type = WHITESPACE;
    static FoundStringMatch lookup_result;
    static Token token;

    while (head < file_string->length) {

        current_char = file_string->start+head;
        head_type = char_type_check(*current_char);

        if (head_type != tail_type) {

            if (head_type == ALPHANUMERIC && is_numeric(*current_char)) {
                head_type = NUMERIC_LITERAL;
            }

            if (tail_type == NUMERIC_LITERAL && is_it_numeric_literal(*current_char)) {
                head_type = NUMERIC_LITERAL;
                continue;
            }

            switch (tail_type) {

                case WHITESPACE:
                    tail = head;
                    tail_type = char_type_check(file_string->start[tail]);
                    continue;

                case ALPHANUMERIC:
                    lookup_result = find_item(&working_table->keyword_table,file_string->start+tail, head-tail);
                    if (lookup_result.status == NO_ERROR) {
                        tail = head;
                        tail_type = char_type_check(file_string->start[tail]);
                        return (Token) {.category = KEYWORD, .data.keyword=lookup_result.node_pointer->token.data.keyword};
                    }

                    lookup_result = find_item(&working_table->symbol_table, file_string->start+tail, head-tail);
                    if (lookup_result.status == NO_ERROR) {
                        tail = head;
                        tail_type = char_type_check(file_string->start[tail]);
                        return (Token) {.category = KEYWORD, .data.keyword=lookup_result.node_pointer->token.data.keyword};
                    }

                    StringArenaPointer arena_pointer = insert_string_to_arena(working_table->string_arena,file_string->start+tail, head-tail);
                    tail = head;
                    tail_type = char_type_check(file_string->start[tail]);
                    return (Token) {.category=IDENTIFIER, .data.identifier = {.value = arena_pointer.string_pointer, .value_length = arena_pointer.string_length}};

                case SYMBOL:
                    lookup_result = find_item(&working_table->operator_table,file_string->start+tail, head-tail);
                    if (lookup_result.status == NO_ERROR) {
                        tail = head;
                        tail_type = char_type_check(file_string->start[tail]);
                        return (Token)  {.category = OPERATOR, .data.operator=lookup_result.node_pointer->token.data.operator};
                    }

                    lookup_result = find_item(&working_table->punctuation_table,file_string->start+tail, head-tail);
                    if (lookup_result.status == NO_ERROR) {
                        tail = head;
                        tail_type = char_type_check(file_string->start[tail]);
                        return (Token)  {.category = PUNCTUATION, .data.punctuation=lookup_result.node_pointer->token.data.punctuation};
                    }
                    break;

                case STRING_LITERAL:
                    break;

                case NUMERIC_LITERAL:
                    arena_pointer = insert_string_to_arena(working_table->string_arena,file_string->start+tail, head-tail);
                    tail = head;
                    tail_type = char_type_check(file_string->start[tail]);
                    return (Token) {.category=IDENTIFIER, .data.identifier = {.value = arena_pointer.string_pointer, .value_length = arena_pointer.string_length}};
            }
        }

        head++;
    }

    return (Token) {.category = UNKNOWN};
}
