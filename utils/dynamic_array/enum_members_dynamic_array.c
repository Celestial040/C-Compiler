#include "dynamic_array/enum_members_dynamic_array.h"
#include "status.h"
#include <stddef.h>
#include <stdlib.h>


Status allocate_enum_members_dynamic_array(EnumMembersDynamicArray *enum_members_dynamic_array, size_t requested_size) {
    EnumMembers *temp = malloc(sizeof(EnumMembers) * requested_size);
    if (temp == NULL) {
        return ALLOCATION_ERROR;
    }

    enum_members_dynamic_array->entries = temp;
    enum_members_dynamic_array->count = 0;
    enum_members_dynamic_array->capacity = requested_size;

    return NO_ERROR;
}

Status reallocate_enum_members_dynamic_array(EnumMembersDynamicArray *enum_members_dynamic_array, size_t requested_size) {
    EnumMembers *temp = realloc(enum_members_dynamic_array->entries,sizeof(EnumMembers) * requested_size);
    if (temp == NULL) {
        return ALLOCATION_ERROR;
    }

    enum_members_dynamic_array->entries = temp;
    enum_members_dynamic_array->capacity = requested_size;

    return NO_ERROR;
}

EnumMembersPointer insert_enum_members(EnumMembersDynamicArray *enum_members_dynamic_array, size_t symbol_id, int64_t value) {
    EnumMembersPointer returned_pointer = {0,NO_ERROR};

    if (enum_members_dynamic_array->count + 1 >= enum_members_dynamic_array->capacity) {
        Status reallocation_status = reallocate_enum_members_dynamic_array(enum_members_dynamic_array, enum_members_dynamic_array->capacity*2);
        if (reallocation_status != NO_ERROR) {
            returned_pointer.status = reallocation_status;
            return returned_pointer;
        }
    }

    returned_pointer.index = enum_members_dynamic_array->count;
    enum_members_dynamic_array->entries[enum_members_dynamic_array->count].symbol_id = symbol_id;
    enum_members_dynamic_array->entries[enum_members_dynamic_array->count].value = value;
    enum_members_dynamic_array->count++;

    return returned_pointer;
}

Status free_enum_members_dynamic_array(EnumMembersDynamicArray *enum_members_dynamic_array) {
    if (enum_members_dynamic_array->entries == NULL || enum_members_dynamic_array->capacity == 0 ) {
        return NULL_POINTER;
    }

    free(enum_members_dynamic_array->entries);
    enum_members_dynamic_array->entries = NULL;
    enum_members_dynamic_array->capacity = 0;
    enum_members_dynamic_array->count = 0;

    return NO_ERROR;
}
