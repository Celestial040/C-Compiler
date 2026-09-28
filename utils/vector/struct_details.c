#include "vector/struct_details.h"
#include "status.h"
#include <stddef.h>
#include <stdlib.h>


Status allocate_struct_details_vector(StructDetailsVector *struct_details_vector, size_t requested_size) {
    StructDetails *temp = malloc(sizeof(StructDetails) * requested_size);
    if (temp == NULL) {
        return ALLOCATION_ERROR;
    }

    struct_details_vector->array = temp;
    struct_details_vector->count = 0;
    struct_details_vector->capacity = requested_size;

    return NO_ERROR;
}

Status reallocate_struct_details_vector(StructDetailsVector *struct_details_vector, size_t requested_size) {
    StructDetails *temp = realloc(struct_details_vector->array,sizeof(StructDetails) * requested_size);
    if (temp == NULL) {
        return ALLOCATION_ERROR;
    }

    struct_details_vector->array = temp;
    struct_details_vector->capacity = requested_size;

    return NO_ERROR;
}

StructDetailsPointer insert_struct_details(StructDetailsVector *struct_details_vector, size_t member_count, size_t start_members_index, size_t total_size) {
    StructDetailsPointer returned_pointer = {0,NO_ERROR};

    if (struct_details_vector->count + 1 >= struct_details_vector->capacity) {
        Status reallocation_status = reallocate_struct_details_vector(struct_details_vector, struct_details_vector->capacity*2);
        if (reallocation_status != NO_ERROR) {
            returned_pointer.status = reallocation_status;
            return returned_pointer;
        }
    }

    returned_pointer.index = struct_details_vector->count;
    struct_details_vector->array[struct_details_vector->count].member_count = member_count;
    struct_details_vector->array[struct_details_vector->count].start_members_index = start_members_index;
    struct_details_vector->array[struct_details_vector->count].total_size = total_size;
    struct_details_vector->count++;

    return returned_pointer;
}

Status struct_details_vector(StructDetailsVector *struct_details_vector) {
    if (struct_details_vector->array == NULL || struct_details_vector->capacity == 0 ) {
        return NULL_POINTER;
    }

    free(struct_details_vector->array);
    struct_details_vector->array = NULL;
    struct_details_vector->capacity = 0;
    struct_details_vector->count = 0;

    return NO_ERROR;
}
