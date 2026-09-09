#include "status.h"
#include <stdio.h>
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



uint64_t hash_string(const char* str, size_t len) {
    uint64_t hash_value = 5381;
    for (size_t i = 0; i < len; i++) {
        hash_value = hash_value * 33 + (unsigned char)str[i];
    }
    return hash_value;
}

Status create_hashmap(HashMap *hashmap, size_t bucket_count) {
    BucketNode *allocated_bucket = (BucketNode *) malloc(sizeof(BucketNode) * bucket_count);
    if (allocated_bucket == NULL) {
        return ALLOCATION_ERROR;
    }
    hashmap->max_bucket_count = bucket_count;
    hashmap->bucketarray = allocated_bucket;

    for (size_t i = 0; i < bucket_count; i++) {
        hashmap->bucketarray[i].hash = 0;
        hashmap->bucketarray[i].string_pointer = NULL;
        hashmap->bucketarray[i].string_length = 0;
        hashmap->bucketarray[i].probe_count = 0;
    }

    return NO_ERROR;
};

void swap_node_value(BucketNode *dest, BucketNode *src) {
    BucketNode tempNode;
    memcpy(&tempNode, dest, sizeof(BucketNode));
    memcpy(dest, src, sizeof(BucketNode));
    memcpy(src, &tempNode, sizeof(BucketNode));
}

bool compare_node(char *string1, size_t string1_length, char *string2, size_t string2_length) {
    if (string1_length == string2_length && memcmp(string1, string2, string1_length) == 0) {
        return true;
    }
    return false;
}

Status insert_item(HashMap *hashmap, char *string, size_t string_length) {
    if (hashmap->current_bucket_count + 1 == hashmap->max_bucket_count) {
        return ARRAY_FULL;
    }
    uint64_t hash_result = hash_string(string, string_length);

    BucketNode new_node;
    new_node.hash = hash_result;
    new_node.string_pointer = string;
    new_node.string_length = string_length;
    new_node.probe_count = 0;


    size_t target_index = hash_result % hashmap->max_bucket_count;
    uint64_t hash_offset = 0;
    BucketNode *target_bucket = hashmap->bucketarray + target_index;

    while (target_bucket->string_pointer != NULL){
        if (compare_node(new_node.string_pointer, new_node.string_length,target_bucket->string_pointer, target_bucket->string_length)) {
            return ITEM_ALREADY_EXIST;
        }
        if (target_bucket->probe_count < new_node.probe_count) {
            swap_node_value(hashmap->bucketarray + target_index, &new_node);
        }
        hash_offset++;
        new_node.probe_count++;
        target_index = (hash_result + hash_offset) % hashmap->max_bucket_count;
        target_bucket = hashmap->bucketarray + target_index;
    }

    memcpy(target_bucket,  &new_node, sizeof(BucketNode));
    hashmap->current_bucket_count++;
    return NO_ERROR;
}

Status check_item(HashMap *hashmap, char *string, size_t string_length) {
    uint64_t hash_result = hash_string(string, string_length);

    size_t target_index = hash_result % hashmap->max_bucket_count;
    uint64_t hash_offset = 0;
    BucketNode *target_bucket = hashmap->bucketarray + target_index;

    while (target_bucket->string_pointer != NULL){
        if (compare_node(string, string_length,target_bucket->string_pointer, target_bucket->string_length)) {
            return NO_ERROR;
        }
        hash_offset++;
        target_index = (hash_result + hash_offset) % hashmap->max_bucket_count;
        target_bucket = hashmap->bucketarray + target_index;
    }

    return ITEM_NOT_FOUND;
}

FoundStringMatch find_item(HashMap *hashmap, char *string, size_t string_length) {
    uint64_t hash_result = hash_string(string, string_length);

    size_t target_index = hash_result % hashmap->max_bucket_count;
    uint64_t hash_offset = 0;
    BucketNode *target_bucket = hashmap->bucketarray + target_index;

    while (target_bucket->string_pointer != NULL){
        if (compare_node(string, string_length,target_bucket->string_pointer, target_bucket->string_length)) {
            return (FoundStringMatch) {.status = NO_ERROR, .node_pointer = target_bucket};
        }
        hash_offset++;
        target_index = (hash_result + hash_offset) % hashmap->max_bucket_count;
        target_bucket = hashmap->bucketarray + target_index;
    }

    return (FoundStringMatch) {.status = ITEM_NOT_FOUND, .node_pointer = NULL};
}
