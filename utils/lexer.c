// #include "char_manip.h"
#include "file_loader.h"
// #include "flat_array_hashmap.h"
#include "status.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include "parser.h"
#include "lexer.h"


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
