#ifndef HASHMAP
#define HASHMAP
#include <stdint.h>
#include <stddef.h>
#include "status.h"

typedef struct BucketNode {
    char *str;
    size_t length;
    size_t count;
    struct BucketNode *next;
} BucketNode;

typedef struct Hashmap {
    BucketNode **bucket;
    size_t bucket_size;
} Hashmap;

uint64_t hash_string(const char* str, size_t len);
Status create_hashmap(Hashmap **hashmap, size_t bucket_size);
Status push_item(Hashmap *hashmap, const char *string, size_t length);
Status search_hashmap(Hashmap *hashmap, const char *string, size_t length, BucketNode **dest);
Status check_if_exist(Hashmap *hashmap, const char *start_pointer, const size_t length);

#endif
