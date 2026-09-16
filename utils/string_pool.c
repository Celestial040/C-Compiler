#include "string_pool.h"
#include "status.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

Status allocate_string_pool(StringPool *string_pool, size_t size_requested) {
    char *allocated_string_pool = (char *) malloc(sizeof(char) * size_requested);
    if (allocated_string_pool == NULL) {
        return ALLOCATION_ERROR;
    }
    string_pool->capacity = size_requested;
    string_pool->start_pointer = allocated_string_pool;
    string_pool->used = 0;

    return NO_ERROR;
}

Status reallocate_string_pool(StringPool *string_pool, size_t size_requested) {
    char *temp = realloc(string_pool->start_pointer, size_requested);
    if (temp == NULL) {
        return ALLOCATION_ERROR;
    }

    string_pool->capacity = size_requested;
    return NO_ERROR;
}

StringPoolPointer insert_string(StringPool *string_pool, const char *string, const size_t string_len) {
    StringPoolPointer return_pointer = {.status = NO_ERROR, .string_length = 0, .string_start = 0};

    if (string_len == 0 || string == NULL || string[0] == '\0') {
        return_pointer.status = STRING_EMPTY;
        return return_pointer;
    }

    if (string_pool->used + string_len >= string_pool->capacity) {
        size_t requested_size = string_pool->capacity * 2;
        if (string_len * 2 > requested_size) {
            requested_size = string_len * 2;
        }
        Status reallocation_status = reallocate_string_pool(string_pool, requested_size);
        if (reallocation_status != NO_ERROR) {
            return_pointer.status = reallocation_status;
            return return_pointer;
        }
    }

    return_pointer.string_start = string_pool->used;
    return_pointer.string_length = string_len;
    strncpy(string_pool->start_pointer + string_pool->used, string, string_len);
    string_pool->start_pointer[string_pool->used + string_len] = '\0';
    string_pool->used += (string_len + 1);

    return return_pointer;
}

Status free_string_pool(StringPool *string_pool) {
    if (string_pool->start_pointer == NULL) {
        return NULL_POINTER;
    }

    free(string_pool->start_pointer);
    string_pool->start_pointer = NULL;
    string_pool->capacity = 0;
    string_pool->used = 0;

    return NO_ERROR;
}
