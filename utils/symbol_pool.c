#include "symbol_pool.h"
#include "status.h"
#include "string_pool.h"
#include <stdlib.h>

Status allocate_symbol_pool(SymbolPool *symbol_pool, StringPool *string_pool, size_t size_requested) {
    SymbolEntry *symbol_entries = (SymbolEntry *) malloc(sizeof(SymbolEntry) * size_requested);
    if (symbol_entries == NULL) {
        return ALLOCATION_ERROR;
    }

    symbol_pool->capacity = size_requested;
    symbol_pool->entries = symbol_entries;
    symbol_pool->count = 0;
    symbol_pool->string_pool = string_pool;

    return NO_ERROR;
}

Status reallocate_symbol_pool(SymbolPool *symbol_pool, size_t size_requested) {
    SymbolEntry *temp = realloc(symbol_pool->entries, size_requested);
    if (temp == NULL) {
        return ALLOCATION_ERROR;
    }

    symbol_pool->capacity = size_requested;
    return NO_ERROR;
}

SymbolEntryPointer insert_symbol(SymbolPool *symbol_pool, const char *string, const size_t string_len) {
    SymbolEntryPointer return_pointer = {.status = NO_ERROR, .symbol_id= NULL};

    if (symbol_pool->count + 1 >= symbol_pool->capacity) {
        Status reallocation_status = reallocate_symbol_pool(symbol_pool, symbol_pool->capacity*2);
        if (reallocation_status != NO_ERROR) {
            return_pointer.status = reallocation_status;
            return return_pointer;
        }
    }

    return_pointer.symbol_id = symbol_pool->count;
    StringPoolPointer string_pointer = insert_string(symbol_pool->string_pool, string, string_len);
    symbol_pool->entries[symbol_pool->count].string_index = string_pointer.string_start;
    symbol_pool->entries[symbol_pool->count].string_length = string_pointer.string_length;
    symbol_pool++;

    return return_pointer;
}


Status free_symbol_pool(SymbolPool *symbol_pool) {
    if (symbol_pool->entries == NULL || symbol_pool->capacity == 0) {
        return NULL_POINTER;
    }

    free(symbol_pool->entries);
    symbol_pool->entries = NULL;
    symbol_pool->string_pool = NULL;
    symbol_pool->capacity = 0;
    symbol_pool->count = 0;

    return NO_ERROR;
}
