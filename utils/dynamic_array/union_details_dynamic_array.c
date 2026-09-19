#include "dynamic_array/union_details_dynamic_array.h"
#include "status.h"
#include <stddef.h>
#include <stdlib.h>


Status allocate_union_details_dynamic_array(UnionDetailsDynamicArray *union_details_dynamic_array, size_t requested_size) {
    UnionDetails *temp = malloc(sizeof(UnionDetails) * requested_size);
    if (temp == NULL) {
        return ALLOCATION_ERROR;
    }

    union_details_dynamic_array->entries = temp;
    union_details_dynamic_array->count = 0;
    union_details_dynamic_array->capacity = requested_size;

    return NO_ERROR;
}

Status reallocate_union_details_dynamic_array(UnionDetailsDynamicArray *union_details_dynamic_array, size_t requested_size) {
    UnionDetails *temp = realloc(union_details_dynamic_array->entries,sizeof(UnionDetails) * requested_size);
    if (temp == NULL) {
        return ALLOCATION_ERROR;
    }

    union_details_dynamic_array->entries = temp;
    union_details_dynamic_array->capacity = requested_size;

    return NO_ERROR;
}

UnionDetailsPointer insert_union_details(UnionDetailsDynamicArray *union_details_dynamic_array, size_t member_count, size_t start_members_index, size_t total_size) {
    UnionDetailsPointer returned_pointer = {0,NO_ERROR};

    if (union_details_dynamic_array->count + 1 >= union_details_dynamic_array->capacity) {
        Status reallocation_status = reallocate_union_details_dynamic_array(union_details_dynamic_array, union_details_dynamic_array->capacity*2);
        if (reallocation_status != NO_ERROR) {
            returned_pointer.status = reallocation_status;
            return returned_pointer;
        }
    }

    returned_pointer.index = union_details_dynamic_array->count;
    union_details_dynamic_array->entries[union_details_dynamic_array->count].member_count = member_count;
    union_details_dynamic_array->entries[union_details_dynamic_array->count].start_members_index = start_members_index;
    union_details_dynamic_array->entries[union_details_dynamic_array->count].total_size = total_size;
    union_details_dynamic_array->count++;

    return returned_pointer;
}

Status union_details_dynamic_array(UnionDetailsDynamicArray *union_details_dynamic_array) {
    if (union_details_dynamic_array->entries == NULL || union_details_dynamic_array->capacity == 0 ) {
        return NULL_POINTER;
    }

    free(union_details_dynamic_array->entries);
    union_details_dynamic_array->entries = NULL;
    union_details_dynamic_array->capacity = 0;
    union_details_dynamic_array->count = 0;

    return NO_ERROR;
}
