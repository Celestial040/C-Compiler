#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

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

uint64_t hash_string(const char* str, size_t len) {
    uint64_t hash_value = 5381;

    for (size_t i = 0; i < len; i++) {
        hash_value = hash_value * 33 + (unsigned char)str[i];
    }

    return hash_value;
}

Status create_hashmap(Hashmap **hashmap, size_t bucket_size){
    Hashmap *new_hashmap = (Hashmap *) calloc(1,sizeof(Hashmap));
    if (new_hashmap == NULL) {
        return ALLOCATION_ERROR;
    }

    new_hashmap->bucket_size = bucket_size;
    new_hashmap->bucket = (BucketNode **)calloc(bucket_size,sizeof(BucketNode*));

    if (new_hashmap->bucket == NULL) {
        free(new_hashmap);
        return ALLOCATION_ERROR;
    }

    *hashmap = new_hashmap;
    return NO_ERROR;
}

Status create_new_bucket(BucketNode **dest, const char *string, const size_t length) {
    BucketNode *new_node = (BucketNode*) calloc(1, sizeof(BucketNode));
    if (new_node == NULL) {
        return ALLOCATION_ERROR;
    }

    new_node->count = 1;
    new_node->next = NULL;
    new_node->length = length;
    new_node->str = (char *) calloc(new_node->length+1,sizeof(char));
    if (new_node->str == NULL) {
        free(new_node);
        return ALLOCATION_ERROR;
    }

    memcpy(new_node->str, string, new_node->length+1);

    *dest = new_node;
    return NO_ERROR;
}

Status push_item(Hashmap *hashmap, const char *string, const size_t length) {
    if (hashmap == NULL) {
        return NULL_POINTER;
    }

    uint64_t hash_value = hash_string(string, length);
    size_t target_index = hash_value % hashmap->bucket_size;
    BucketNode *target = hashmap->bucket[target_index];

    BucketNode *last = NULL;
    while (target != NULL) {
        if (target->length == length && memcmp(target->str, string, length) == 0) {
            target->count++;
            return NO_ERROR;
        }
        last = target;
        target = target->next;
    }

    BucketNode *new_node;
    Status status = create_new_bucket(&new_node, string, length);
    if (status != 0) {
        return status;
    }

    if (last == NULL) {
        hashmap->bucket[target_index] = new_node;
    }
    else {
        last->next = new_node;
    }

    return NO_ERROR;
}

Status search_hashmap(Hashmap *hashmap, const char *string, const size_t length, BucketNode **dest) {
    if (hashmap == NULL) {
        return NULL_POINTER;
    }

    uint64_t hash_value = hash_string(string, length);
    size_t target_index = hash_value % hashmap->bucket_size;
    BucketNode *target = hashmap->bucket[target_index];

    if (target == NULL) {
        return ITEM_NOT_FOUND;
    }

    while (target != NULL) {
        if (target->length == length && memcmp(target->str, string, length) == 0) {
            *dest = target;
            return NO_ERROR;
        }

        target = target->next;
    }

    return ITEM_NOT_FOUND;
}

Status check_if_exist(Hashmap *hashmap, const char *start_pointer, const size_t length) {
    if (hashmap == NULL) {
        return NULL_POINTER;
    }

    uint64_t hash_value = hash_string(start_pointer, length);
    size_t target_index = hash_value % hashmap->bucket_size;
    BucketNode *target = hashmap->bucket[target_index];

    if (target == NULL) {
        return ITEM_NOT_FOUND;
    }

    while (target != NULL) {
        if (target->length == length && memcmp(target->str, start_pointer, length) == 0) {
            return NO_ERROR;
        }

        target = target->next;
    }

    return ITEM_NOT_FOUND;
}
