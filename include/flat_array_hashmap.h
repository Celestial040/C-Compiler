#ifndef FLAT_ARRAY_HASHMAP_H
#define FLAT_ARRAY_HASHMAP_H


#include "string_arena_allocator.h"
#include "token.h"
#include "status.h"
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct BucketNode{
    uint64_t hash;
    const char *string_pointer;
    size_t string_length;
    size_t probe_count;
    Token token;
}BucketNode;

typedef struct HashMap {
    BucketNode *bucketarray;
    size_t max_bucket_count;
    size_t current_bucket_count;

} HashMap;

typedef struct FoundStringMatch {
    Status status;
    BucketNode *node_pointer;
} FoundStringMatch;

typedef struct TablesGroup {
    HashMap keyword_table;
    HashMap operator_table;
    HashMap punctuation_table;
    HashMap symbol_table;
    StringArenaMemory *string_arena;
} TablesGroup;


uint64_t hash_string(const char* str, size_t len);
Status create_hashmap(HashMap *hashmap, size_t bucket_count);
Status insert_item(HashMap *hashmap, const char *string, const size_t string_length,Token token_representative);
Status check_item(HashMap *hashmap, const char *string, size_t string_length);
FoundStringMatch find_item(HashMap *hashmap, const char *string, size_t string_length);

#endif
