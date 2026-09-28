#include "vector/union_details.h"
#include "status.h"
#include <stddef.h>
#include <stdlib.h>


Status allocate_union_details_vector(UnionDetailsVector *union_details_vector, size_t requested_size) {
    UnionDetails *temp = malloc(sizeof(UnionDetails) * requested_size);
    if (temp == NULL) {
        return ALLOCATION_ERROR;
    }

    union_details_vector->array = temp;
    union_details_vector->count = 0;
    union_details_vector->capacity = requested_size;

    return NO_ERROR;
}

Status reallocate_union_details_vector(UnionDetailsVector *union_details_vector, size_t requested_size) {
    UnionDetails *temp = realloc(union_details_vector->array,sizeof(UnionDetails) * requested_size);
    if (temp == NULL) {
        return ALLOCATION_ERROR;
    }

    union_details_vector->array = temp;
    union_details_vector->capacity = requested_size;

    return NO_ERROR;
}

UnionDetailsPointer insert_union_details(UnionDetailsVector *union_details_vector, size_t member_count, size_t start_members_index, size_t total_size) {
    UnionDetailsPointer returned_pointer = {0,NO_ERROR};

    if (union_details_vector->count + 1 >= union_details_vector->capacity) {
        Status reallocation_status = reallocate_union_details_vector(union_details_vector, union_details_vector->capacity*2);
        if (reallocation_status != NO_ERROR) {
            returned_pointer.status = reallocation_status;
            return returned_pointer;
        }
    }

    returned_pointer.index = union_details_vector->count;
    union_details_vector->array[union_details_vector->count].member_count = member_count;
    union_details_vector->array[union_details_vector->count].start_members_index = start_members_index;
    union_details_vector->array[union_details_vector->count].total_size = total_size;
    union_details_vector->count++;

    return returned_pointer;
}

Status union_details_vector(UnionDetailsVector *union_details_vector) {
    if (union_details_vector->array == NULL || union_details_vector->capacity == 0 ) {
        return NULL_POINTER;
    }

    free(union_details_vector->array);
    union_details_vector->array = NULL;
    union_details_vector->capacity = 0;
    union_details_vector->count = 0;

    return NO_ERROR;
}
