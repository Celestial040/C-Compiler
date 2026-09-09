#ifndef FLAT_ARRAY_HASHMAP
#define FLAT_ARRAY_HASHMAP


#include "file_loader.h"
#include "status.h"
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct BucketNode{
    uint64_t hash;
    char *string_pointer;
    size_t string_length;
    size_t probe_count;
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


uint64_t hash_string(const char* str, size_t len);
Status create_hashmap(HashMap *hashmap, size_t bucket_count);
Status insert_item(HashMap *hashmap, char *string, size_t string_length);
Status check_item(HashMap *hashmap, char *string, size_t string_length);
FoundStringMatch find_item(HashMap *hashmap, char *string, size_t string_length);

#endif
