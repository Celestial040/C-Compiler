#include "dynamic_array/enum_details_dynamic_array.h"
#include "status.h"
#include <stddef.h>
#include <stdlib.h>


Status allocate_enum_details_dynamic_array(EnumDetailsDynamicArray *enum_details_dynamic_array, size_t requested_size) {
    EnumDetails *temp = malloc(sizeof(EnumDetails) * requested_size);
    if (temp == NULL) {
        return ALLOCATION_ERROR;
    }

    enum_details_dynamic_array->entries = temp;
    enum_details_dynamic_array->count = 0;
    enum_details_dynamic_array->capacity = requested_size;

    return NO_ERROR;
}

Status reallocate_enum_details_dynamic_array(EnumDetailsDynamicArray *enum_details_dynamic_array, size_t requested_size) {
    EnumDetails *temp = realloc(enum_details_dynamic_array->entries,sizeof(EnumDetails) * requested_size);
    if (temp == NULL) {
        return ALLOCATION_ERROR;
    }

    enum_details_dynamic_array->entries = temp;
    enum_details_dynamic_array->capacity = requested_size;

    return NO_ERROR;
}

EnumDetailsPointer insert_enum_details(EnumDetailsDynamicArray *enum_details_dynamic_array, size_t member_count, size_t start_members_index) {
    EnumDetailsPointer returned_pointer = {0,NO_ERROR};

    if (enum_details_dynamic_array->count + 1 >= enum_details_dynamic_array->capacity) {
        Status reallocation_status = reallocate_enum_details_dynamic_array(enum_details_dynamic_array, enum_details_dynamic_array->capacity*2);
        if (reallocation_status != NO_ERROR) {
            returned_pointer.status = reallocation_status;
            return returned_pointer;
        }
    }

    returned_pointer.index = enum_details_dynamic_array->count;
    enum_details_dynamic_array->entries[enum_details_dynamic_array->count].member_count = member_count;
    enum_details_dynamic_array->entries[enum_details_dynamic_array->count].start_members_index = start_members_index;
    enum_details_dynamic_array->count++;

    return returned_pointer;
}

Status enum_details_dynamic_array(EnumDetailsDynamicArray *enum_details_dynamic_array) {
    if (enum_details_dynamic_array->entries == NULL || enum_details_dynamic_array->capacity == 0 ) {
        return NULL_POINTER;
    }

    free(enum_details_dynamic_array->entries);
    enum_details_dynamic_array->entries = NULL;
    enum_details_dynamic_array->capacity = 0;
    enum_details_dynamic_array->count = 0;

    return NO_ERROR;
}
