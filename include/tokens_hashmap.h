#ifndef TOKENS_HASHMAP_H
#define TOKENS_HASHMAP_H

#include "status.h"
#include "symbol_pool.h"
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>


typedef struct HashSlot {
    size_t symbol_id;
    uint32_t hash;
    uint32_t probe_count;
} HashSlot;

typedef struct TokensHashMap {
    HashSlot *slots;
    size_t capacity;
    size_t count;
    size_t mask;
    SymbolPool *symbol_pool;
} TokensHashMap;

Status allocate_hashmap(TokensHashMap *hashmap, SymbolPool *symbol_pool, size_t bucket_count);
Status insert_item(TokensHashMap *hashmap, const char *string, const size_t string_length, size_t symbol_id);
TokenStatus lookup_item(TokensHashMap *hashmap, const char *string, const size_t string_length, size_t line);

#endif
