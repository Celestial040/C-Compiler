#include "vector/string.h"
#include "status.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Status allocate_string_vector(StringVector *string_vector, size_t size_requested) {
    char *allocated_string_vector = (char *) malloc(sizeof(char) * size_requested);
    if (allocated_string_vector == NULL) {
        return ALLOCATION_ERROR;
    }
    string_vector->capacity = size_requested;
    string_vector->start_pointer = allocated_string_vector;
    string_vector->used = 0;

    return NO_ERROR;
}

Status reallocate_string_vector(StringVector *string_vector, size_t size_requested) {
    char *temp = realloc(string_vector->start_pointer, sizeof(char) * size_requested);
    if (temp == NULL) {
        return ALLOCATION_ERROR;
    }
    string_vector->start_pointer = temp;
    string_vector->capacity = size_requested;
    return NO_ERROR;
}

StringVectorPointer insert_string(StringVector *string_vector, const char *string, const size_t string_len) {

    StringVectorPointer return_pointer = {NO_ERROR, 0, 0};
    Status reallocation_status;
    size_t requested_size;

    if (string_len == 0 || string == NULL || string[0] == '\0') {
        return_pointer.status = STRING_EMPTY;
        return return_pointer;
    }

    if (string_vector->used + string_len + 1 >= string_vector->capacity) {
        requested_size = string_vector->capacity * 2;
        if (string_len + 1 > requested_size) {
            requested_size = string_len * 2;
        }
        reallocation_status = reallocate_string_vector(string_vector, requested_size);
        if (reallocation_status != NO_ERROR) {
            return_pointer.status = reallocation_status;
            return return_pointer;
        }
    }

    return_pointer.string_start = string_vector->used;
    return_pointer.string_length = string_len;
    strncpy(string_vector->start_pointer + string_vector->used, string, string_len);
    string_vector->start_pointer[string_vector->used + string_len] = '\0';
    string_vector->used += (string_len + 1);

    return return_pointer;
}

Status free_string_vector(StringVector *string_vector) {
    if (string_vector->start_pointer == NULL) {
        return NULL_POINTER;
    }

    free(string_vector->start_pointer);
    string_vector->start_pointer = NULL;
    string_vector->capacity = 0;
    string_vector->used = 0;

    return NO_ERROR;
}
