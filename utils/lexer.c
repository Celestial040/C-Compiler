#include "lexer.h"
#include "char_manip.h"
#include "status.h"
#include "dynamic_array/symbol_dynamic_array.h"
#include "tokens_hashmap.h"
#include <stddef.h>
#include <stdio.h>
#include <stdnoreturn.h>

typedef enum CharType {
    WHITESPACE,
    ALPHANUMERIC,
    SYMBOL,
    STRING_LITERAL,
    NUMERIC_LITERAL,
    FLOAT_LITERAL
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

Token lexer_scan(TokensHashMap *tokens_table, FileString *file_string) {
    static size_t head, tail  = 0;
    static char *current_char = NULL;
    static CharType head_type, tail_type = WHITESPACE;
    static TokenStatus lookup_result;
    static Token token_result = {0,TOKEN_UNKNOWN,SYMBOL_NONE,0};
    static size_t lines = 1;


    while (head < file_string->length) {
        current_char = file_string->start+head;
        head_type = char_type_check(*current_char);
        printf("mode : %d, %d \n",head_type, tail_type);
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
                        head++;
                        return token_result;
                    }

                    token_result.token_type = TOKEN_UNKNOWN;
                    token_result.line = lines;
                    tail = head;
                    tail_type = char_type_check(file_string->start[tail]);
                    head++;
                    return token_result;

                case SYMBOL:
                    lookup_result = lookup_item(tokens_table, file_string->start+tail , head - tail, lines);
                    if (lookup_result.status == NO_ERROR) {
                        token_result = lookup_result.token;
                        tail = head;
                        tail_type = char_type_check(file_string->start[tail]);
                        head++;
                        return token_result;
                    }
                    token_result.token_type = TOKEN_UNKNOWN;
                    token_result.line = lines;
                    tail = head;
                    tail_type = char_type_check(file_string->start[tail]);
                    head++;
                    return token_result;

                case STRING_LITERAL:
                    break;

                case NUMERIC_LITERAL:
                    break;

                case FLOAT_LITERAL:
                    break;


            }

        }
        head++;
    }
    return token_result;
}
