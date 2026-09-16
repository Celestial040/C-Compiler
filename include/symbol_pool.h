#ifndef SYMBOL_POOL_H
#define SYMBOL_POOL_H

#include "status.h"
#include "string_pool.h"
#include <stddef.h>
#include <stdint.h>

typedef uint8_t SymbolType;
enum {
    SYMBOL_NONE,
    SYMBOL_KEYWORD,
    SYMBOL_OPERATOR,
    SYMBOL_PUNCTUATION,
    SYMBOL_IDENTIFIER,
    SYMBOL_TYPEDEF_NAME,
    SYMBOL_VARIABLE,
    SYMBOL_FUNCTION,
    SYMBOL_STRUCT_TAG,
    SYMBOL_UNION_TAG,
    SYMBOL_ENUM_TAG,
    SYMBOL_ENUM_CONSTANT
};

typedef struct SymbolEntry {
    size_t string_index;
    size_t string_length;
    size_t scope_depth;
    void *details;
    uint32_t added_attributes;
    SymbolType symbol_type;
} SymbolEntry;

typedef struct SymbolPool {
    SymbolEntry *entries;
    size_t count;
    size_t capacity;
    StringPool *string_pool;
} SymbolPool;

typedef struct SymbolEntryPointer {
    size_t symbol_id;
    Status status;
} SymbolEntryPointer;

Status allocate_symbol_pool(SymbolPool *symbol_pool, StringPool *string_pool, size_t size_requested);
SymbolEntryPointer insert_symbol(SymbolPool *symbol_pool, const char *string, const size_t string_len);
Status free_symbol_pool(SymbolPool *symbol_pool);

#endif
