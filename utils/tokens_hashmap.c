#include "tokens_hashmap.h"
#include "fnv1a32.h"
#include "status.h"
#include "string_pool.h"
#include "symbol_pool.h"
#include "bool.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


Status allocate_hashmap(TokensHashMap *hashmap, SymbolPool *symbol_pool, size_t bucket_count) {
    HashSlot *allocated_slot = (HashSlot *) calloc(sizeof(HashSlot),bucket_count);
    if (allocated_slot == NULL) {
        return ALLOCATION_ERROR;
    }

    hashmap->capacity = bucket_count;
    hashmap->count = 0;
    hashmap->slots = allocated_slot;
    hashmap->symbol_pool = symbol_pool;

    return NO_ERROR;
}

bool compare_slot(SymbolPool *symbol_pool, HashSlot *slot1, HashSlot *slot2) {
    SymbolEntry *slot1_entry = symbol_pool->entries + slot1->symbol_id;
    SymbolEntry *slot2_entry = symbol_pool->entries + slot2->symbol_id;
    StringPool *string_pool = symbol_pool->string_pool;
    if (slot1_entry->string_length == slot2_entry->string_length &&
        memcmp(string_pool+slot1_entry->string_index, string_pool+slot2_entry->string_index, slot1_entry->string_length) == 0) {
        return true;
    }
    return false;
}

bool compare_string(const char *string1, const size_t string_length1, const char *string2, const size_t string_length2) {
    if (string_length1 == string_length2 && memcmp(string1, string2, string_length1) == 0) {
        return true;
    }
    return false;
}

void swap_slot(HashSlot *slot1, HashSlot *slot2) {
    HashSlot temp;
    memcpy(&temp, slot1, sizeof(HashSlot));
    memcpy(slot1, slot2, sizeof(HashSlot));
    memcpy(slot2, &temp, sizeof(HashSlot));
}

Status rehash_hashmap(TokensHashMap *hashmap, size_t resize_target_size) {
    HashSlot *temp;
    HashSlot tempSlot;

    size_t i;
    size_t target_index;
    size_t hash_offset;

    temp = (HashSlot *) calloc(sizeof(HashSlot),resize_target_size);
    if (temp == NULL) {
        return ALLOCATION_ERROR;
    }


    for (i = 0; i < hashmap->count; i++) {
        if (hashmap->slots[i].hash == 0) {
            continue;
        }

        tempSlot.hash = hashmap->slots[i].hash;
        tempSlot.symbol_id = hashmap->slots[i].symbol_id;
        tempSlot.probe_count = 0;

        target_index = hashmap->slots[i].hash % resize_target_size;
        hash_offset = 0;

        while (temp[target_index].hash != 0) {
            if (temp[target_index].hash != tempSlot.hash) {
                continue;
            }
            if (compare_slot(hashmap->symbol_pool, temp+target_index, &tempSlot)) {
                return ITEM_ALREADY_EXIST;
            }
            if (temp[target_index].probe_count < tempSlot.probe_count) {
                swap_slot(temp+target_index, &tempSlot);
            }

            target_index = (hashmap->slots[i].hash + hash_offset) % resize_target_size;
            hash_offset++;
            tempSlot.probe_count++;
        }
        memcpy(temp+target_index, &tempSlot, sizeof(HashSlot));
    }
    free(hashmap->slots);
    hashmap->slots = temp;
    hashmap->capacity = resize_target_size;
    hashmap->capacity = resize_target_size;
    return NO_ERROR;
}

Status insert_item(TokensHashMap *hashmap, const char *string, const size_t string_length, size_t symbol_id) {
    Status reallocation_status;

    uint32_t hash_result = fnv1a32(string, string_length);
    HashSlot tempSlot;

    size_t target_index = hash_result % hashmap->capacity;
    size_t hash_offset = 0;

    if (hashmap->count + 1 >= hashmap->capacity * 0.6) {
       reallocation_status = rehash_hashmap(hashmap, hashmap->capacity*2);
       if (reallocation_status != NO_ERROR) {
           return reallocation_status;
       }
    }

    tempSlot.hash = hash_result;
    tempSlot.symbol_id = symbol_id;
    tempSlot.probe_count = 0;

    while (hashmap->slots[target_index].hash != 0) {
        if (hashmap->slots[target_index].hash != tempSlot.hash) {
            hash_offset++;
            target_index = (hash_result + hash_offset) % hashmap->capacity;
            tempSlot.probe_count++;
            continue;
        }
        if (compare_slot(hashmap->symbol_pool, hashmap->slots+target_index, &tempSlot)) {
            return ITEM_ALREADY_EXIST;
        }
        if (hashmap->slots[target_index].probe_count < tempSlot.probe_count) {
            swap_slot(hashmap->slots+target_index, &tempSlot);
        }

        hash_offset++;
        target_index = (hash_result + hash_offset) % hashmap->capacity;
        tempSlot.probe_count++;
    }
    memcpy(hashmap->slots+target_index, &tempSlot, sizeof(HashSlot));
    hashmap->count++;


    return NO_ERROR;
}


TokenStatus lookup_item(TokensHashMap *hashmap, const char *string, const size_t string_length, size_t line) {
    uint32_t hash_result = fnv1a32(string, string_length);

    size_t target_index = hash_result % hashmap->capacity;
    uint64_t hash_offset = 0;

    SymbolPool *symbol_pool = hashmap->symbol_pool;
    StringPool *string_pool = symbol_pool->string_pool;

    Token returned_token;
    TokenStatus returned_status;

    HashSlot *target_slot;
    uint32_t symbol_id;
    const char *stored_string;
    size_t stored_length;


    while (hashmap->slots[target_index].hash != 0) {
        target_slot = &hashmap->slots[target_index];
        symbol_id = target_slot->symbol_id;

        stored_string = string_pool->start_pointer + symbol_pool->entries[symbol_id].string_index;
        stored_length = symbol_pool->entries[symbol_id].string_length;

        if (compare_string(string, string_length, stored_string, stored_length)) {

            returned_token.token_type = symbol_pool->entries[symbol_id].semantic.token_type;
            returned_token.sub_token_type = symbol_pool->entries[symbol_id].semantic.sub_token_type;
            returned_token.symbol_id = symbol_id;
            returned_token.line = line;

            returned_status.status = NO_ERROR;
            returned_status.token = returned_token;

            return returned_status;
        }

        hash_offset++;
        target_index = (hash_result + hash_offset) % hashmap->capacity;
    }

    returned_status.status = ITEM_NOT_FOUND;
    returned_token.token_type = TOKEN_UNKNOWN;
    returned_status.token = returned_token;
    return returned_status;
}
