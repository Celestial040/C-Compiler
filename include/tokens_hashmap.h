#ifndef TOKENS_HASHMAP_H
#define TOKENS_HASHMAP_H

#include "status.h"
#include "vector/symbol.h"
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>

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
    SymbolVector *symbol_vector;
} TokensHashMap;

Status allocate_hashmap(TokensHashMap *hashmap, SymbolVector *symbol_vector, size_t bucket_count);
Status insert_item(TokensHashMap *hashmap, const char *string, const size_t string_length, size_t symbol_id);
TokenStatus lookup_item(TokensHashMap *hashmap, const char *string, const size_t string_length, size_t line);
Status free_hashmap(TokensHashMap *hashmap);

#endif
