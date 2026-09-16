#include "tokens_hashmap.h"
#include "fnv1a32.h"
#include "status.h"
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>


Status init_hashmap(TokensHashMap *hashmap, size_t bucket_count) {
    HashSlot *allocated_slot = (HashSlot *) calloc(sizeof(HashSlot),bucket_count);
    if (allocated_slot == NULL) {
        return ALLOCATION_ERROR;
    }

    hashmap->capacity = bucket_count;
    hashmap->count = 0;
    hashmap->slots = allocated_slot;

    return NO_ERROR;
};

Status rehash_hashmap(TokensHashMap *hashmap, size_t resize_target_size) {
    HashSlot *temp = (HashSlot *)  calloc(sizeof(HashSlot),resize_target_size);
    if (temp == NULL) {
        return ALLOCATION_ERROR;
    }

    for (size_t i = 0 ; i < hashmap->count; i++) {
        if (hashmap->slots[i].hash == 0) {
            continue;
        }
    }
    free(hashmap->slots);
    hashmap->slots = temp;
    hashmap->capacity = resize_target_size;
    hashmap->capacity = resize_target_size;
    return NO_ERROR;
}

Status insert_item(TokensHashMap *hashmap, const char *string, const size_t string_length, size_t symbol_id) {
    if (hashmap->count + 1 >= hashmap->capacity * 0.6) {
       Status reallocation_status = rehash_hashmap(hashmap, hashmap->capacity*2);
       if (reallocation_status != NO_ERROR) {
           return reallocation_status;
       }
    }

    uint32_t hash_result = fnv1a32(string, string_length);

}
