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



Token scan(TablesGroup *working_table, FileString *file_string) {
    static size_t head = 0;
    static size_t tail = 0;
    static bool alphanum_state = true;
    static char *current_char = NULL;

    // printf("%ld", head);
    // printf("%ld", tail);

    // printf("\n");

    while (head < file_string->length) {
        current_char = file_string->start+head;

        if (!is_alphabet_numeric(*current_char)) {
            if (alphanum_state) {
                alphanum_state = false;

                FoundStringMatch lookup_result = find_item(&working_table->keyword_table,file_string->start+tail, head-tail);
                if (lookup_result.status == NO_ERROR) {
                    return (Token) {.category = KEYWORD, .data.keyword=lookup_result.node_pointer->token.data.keyword};
                }

                lookup_result = find_item(&working_table->operator_table,file_string->start+tail, head-tail);
                if (lookup_result.status == NO_ERROR) {
                    return (Token) {.category = OPERATOR, .data.operator=lookup_result.node_pointer->token.data.operator};
                }

                lookup_result = find_item(&working_table->punctuation_table,file_string->start+tail, head-tail);
                if (lookup_result.status == NO_ERROR) {
                    return (Token) {.category = PUNCTUATION, .data.punctuation=lookup_result.node_pointer->token.data.punctuation};
                }

                StringArenaPointer arena_pointer = insert_string_to_arena(working_table->string_arena,file_string->start+tail, head-tail);
                Token identifier = {.category=IDENTIFIER, .data.identifier = {.value = arena_pointer.string_pointer, .value_length = arena_pointer.string_length}};
                insert_item(&working_table->symbol_table, arena_pointer.string_pointer, arena_pointer.string_length,identifier);
                return identifier;

            } else if (is_whitespace(*current_char)){
                head++;
                continue;
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

    return (Token) {.category = UNKNOWN};
}
