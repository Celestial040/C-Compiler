#include "vector/enum_details.h"
#include "status.h"
#include <stddef.h>
#include <stdlib.h>


Status allocate_enum_details_vector(EnumDetailsVector *enum_details_vector, size_t requested_size) {
    EnumDetails *temp = malloc(sizeof(EnumDetails) * requested_size);
    if (temp == NULL) {
        return ALLOCATION_ERROR;
    }

    enum_details_vector->array = temp;
    enum_details_vector->count = 0;
    enum_details_vector->capacity = requested_size;

    return NO_ERROR;
}

Status reallocate_enum_details_vector(EnumDetailsVector *enum_details_vector, size_t requested_size) {
    EnumDetails *temp = realloc(enum_details_vector->array,sizeof(EnumDetails) * requested_size);
    if (temp == NULL) {
        return ALLOCATION_ERROR;
    }

    enum_details_vector->array = temp;
    enum_details_vector->capacity = requested_size;

    return NO_ERROR;
}

EnumDetailsPointer insert_enum_details(EnumDetailsVector *enum_details_vector, size_t member_count, size_t start_members_index) {
    EnumDetailsPointer returned_pointer = {0,NO_ERROR};

    if (enum_details_vector->count + 1 >= enum_details_vector->capacity) {
        Status reallocation_status = reallocate_enum_details_vector(enum_details_vector, enum_details_vector->capacity*2);
        if (reallocation_status != NO_ERROR) {
            returned_pointer.status = reallocation_status;
            return returned_pointer;
        }
    }

    returned_pointer.index = enum_details_vector->count;
    enum_details_vector->array[enum_details_vector->count].member_count = member_count;
    enum_details_vector->array[enum_details_vector->count].start_members_index = start_members_index;
    enum_details_vector->count++;

    return returned_pointer;
}

Status enum_details_vector(EnumDetailsVector *enum_details_vector) {
    if (enum_details_vector->array == NULL || enum_details_vector->capacity == 0 ) {
        return NULL_POINTER;
    }

    free(enum_details_vector->array);
    enum_details_vector->array = NULL;
    enum_details_vector->capacity = 0;
    enum_details_vector->count = 0;

    return NO_ERROR;
}
