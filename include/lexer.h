#ifndef NEW_LEXER_H
#define NEW_LEXER_H

#include "file_loader.h"
#include "symbol_pool.h"
#include "tokens_hashmap.h"

Token lexer_scan(TokensHashMap *tokens_table, FileString *file_string);

#endif
