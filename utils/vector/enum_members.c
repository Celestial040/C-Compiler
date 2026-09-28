#include "vector/enum_members.h"
#include "status.h"
#include <stddef.h>
#include <stdlib.h>


Status allocate_enum_members_vector(EnumMembersVector *enum_members_vector, size_t requested_size) {
    EnumMembers *temp = malloc(sizeof(EnumMembers) * requested_size);
    if (temp == NULL) {
        return ALLOCATION_ERROR;
    }

    enum_members_vector->array = temp;
    enum_members_vector->count = 0;
    enum_members_vector->capacity = requested_size;

    return NO_ERROR;
}

Status reallocate_enum_members_vector(EnumMembersVector *enum_members_vector, size_t requested_size) {
    EnumMembers *temp = realloc(enum_members_vector->array,sizeof(EnumMembers) * requested_size);
    if (temp == NULL) {
        return ALLOCATION_ERROR;
    }

    enum_members_vector->array = temp;
    enum_members_vector->capacity = requested_size;

    return NO_ERROR;
}

EnumMembersPointer insert_enum_members(EnumMembersVector *enum_members_vector, size_t symbol_id, int64_t value) {
    EnumMembersPointer returned_pointer = {0,NO_ERROR};

    if (enum_members_vector->count + 1 >= enum_members_vector->capacity) {
        Status reallocation_status = reallocate_enum_members_vector(enum_members_vector, enum_members_vector->capacity*2);
        if (reallocation_status != NO_ERROR) {
            returned_pointer.status = reallocation_status;
            return returned_pointer;
        }
    }

    returned_pointer.index = enum_members_vector->count;
    enum_members_vector->array[enum_members_vector->count].symbol_id = symbol_id;
    enum_members_vector->array[enum_members_vector->count].value = value;
    enum_members_vector->count++;

    return returned_pointer;
}

Status free_enum_members_vector(EnumMembersVector *enum_members_vector) {
    if (enum_members_vector->array == NULL || enum_members_vector->capacity == 0 ) {
        return NULL_POINTER;
    }

    free(enum_members_vector->array);
    enum_members_vector->array = NULL;
    enum_members_vector->capacity = 0;
    enum_members_vector->count = 0;

    return NO_ERROR;
}
