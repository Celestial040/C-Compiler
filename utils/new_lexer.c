#include "new_lexer.h"
#include "char_manip.h"
#include "status.h"
#include "symbol_pool.h"
#include "tokens_hashmap.h"
#include <stddef.h>
#include <stdio.h>

typedef enum CharType {
    WHITESPACE,
    ALPHANUMERIC,
    SYMBOL,
    STRING_LITERAL,
    NUMERIC_LITERAL
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

Token scan_parser(TokensHashMap *tokens_table, FileString *file_string) {
    static size_t head, tail  = 0;
    static char *current_char = NULL;
    static CharType head_type, tail_type = WHITESPACE;
    static TokenStatus lookup_result;
    static Token token_result;
    static size_t lines = 1;


    while (head < file_string->length) {
        current_char = file_string->start+head;
        head_type = char_type_check(*current_char);
        printf("%ld , %ld \n", head,tail);

        if (head_type != tail_type) {
            if (head_type == ALPHANUMERIC && is_numeric(*current_char)) {
                head_type = NUMERIC_LITERAL;
            }

            if (tail_type == NUMERIC_LITERAL && is_it_numeric_literal(*current_char)) {
                head_type = NUMERIC_LITERAL;
                continue;
            }

            if (*current_char == '\n') {
                lines++;
            }

            switch (tail_type) {
                case WHITESPACE:
                    tail = head;
                    tail_type = char_type_check(file_string->start[tail]);
                    head++;
                    continue;

                case ALPHANUMERIC:
                    lookup_result = lookup_item(tokens_table, file_string->start+tail , head - tail, lines);
                    if (lookup_result.status == NO_ERROR) {
                        token_result = lookup_result.token;
                        tail = head;
                        tail_type = char_type_check(file_string->start[tail]);
                        return token_result;
                    }

                    token_result.token_type = TOKEN_UNKNOWN;
                    token_result.line = lines;
                    return token_result;

                case SYMBOL:
                    lookup_result = lookup_item(tokens_table, file_string->start+tail , head - tail, lines);
                    if (lookup_result.status == NO_ERROR) {
                        token_result = lookup_result.token;
                        tail = head;
                        tail_type = char_type_check(file_string->start[tail]);
                        return token_result;
                    }
                    token_result.token_type = TOKEN_UNKNOWN;
                    token_result.line = lines;
                    return token_result;

                case STRING_LITERAL:
                    break;

/*                 case NUMERIC_LITERAL:
                    arena_pointer = insert_string_to_arena(working_table->string_arena,file_string->start+tail, head-tail);
                    tail = head;
                    tail_type = char_type_check(file_string->start[tail]);
                    return (Token) {.category=IDENTIFIER, .data.identifier = {.value = arena_pointer.string_pointer, .value_length = arena_pointer.string_length}}; */


            }

        }
        head++;
    }
}
