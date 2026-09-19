#include "dynamic_array/struct_details_dynamic_array.h"
#include "status.h"
#include <stddef.h>
#include <stdlib.h>


Status allocate_struct_details_dynamic_array(StructDetailsDynamicArray *struct_details_dynamic_array, size_t requested_size) {
    StructDetails *temp = malloc(sizeof(StructDetails) * requested_size);
    if (temp == NULL) {
        return ALLOCATION_ERROR;
    }

    struct_details_dynamic_array->entries = temp;
    struct_details_dynamic_array->count = 0;
    struct_details_dynamic_array->capacity = requested_size;

    return NO_ERROR;
}

Status reallocate_struct_details_dynamic_array(StructDetailsDynamicArray *struct_details_dynamic_array, size_t requested_size) {
    StructDetails *temp = realloc(struct_details_dynamic_array->entries,sizeof(StructDetails) * requested_size);
    if (temp == NULL) {
        return ALLOCATION_ERROR;
    }

    struct_details_dynamic_array->entries = temp;
    struct_details_dynamic_array->capacity = requested_size;

    return NO_ERROR;
}

StructDetailsPointer insert_struct_details(StructDetailsDynamicArray *struct_details_dynamic_array, size_t member_count, size_t start_members_index, size_t total_size) {
    StructDetailsPointer returned_pointer = {0,NO_ERROR};

    if (struct_details_dynamic_array->count + 1 >= struct_details_dynamic_array->capacity) {
        Status reallocation_status = reallocate_struct_details_dynamic_array(struct_details_dynamic_array, struct_details_dynamic_array->capacity*2);
        if (reallocation_status != NO_ERROR) {
            returned_pointer.status = reallocation_status;
            return returned_pointer;
        }
    }

    returned_pointer.index = struct_details_dynamic_array->count;
    struct_details_dynamic_array->entries[struct_details_dynamic_array->count].member_count = member_count;
    struct_details_dynamic_array->entries[struct_details_dynamic_array->count].start_members_index = start_members_index;
    struct_details_dynamic_array->entries[struct_details_dynamic_array->count].total_size = total_size;
    struct_details_dynamic_array->count++;

    return returned_pointer;
}

Status struct_details_dynamic_array(StructDetailsDynamicArray *struct_details_dynamic_array) {
    if (struct_details_dynamic_array->entries == NULL || struct_details_dynamic_array->capacity == 0 ) {
        return NULL_POINTER;
    }

    free(struct_details_dynamic_array->entries);
    struct_details_dynamic_array->entries = NULL;
    struct_details_dynamic_array->capacity = 0;
    struct_details_dynamic_array->count = 0;

    return NO_ERROR;
}
