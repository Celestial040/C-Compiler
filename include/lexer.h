#ifndef LEXER_H
#define LEXER_H

#include "file_loader.h"
#include "flat_array_hashmap.h"
#include "token.h"
// #include "status.h"


Token scan(TablesGroup *working_table, FileString *file_string);

#endif
