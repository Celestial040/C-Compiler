#include "vector/union_members.h"
#include "status.h"
#include <stddef.h>
#include <stdlib.h>


Status allocate_union_members_vector(UnionMembersVector *union_members_vector, size_t requested_size) {
    UnionMembers *temp = malloc(sizeof(UnionMembers) * requested_size);
    if (temp == NULL) {
        return ALLOCATION_ERROR;
    }

    union_members_vector->array = temp;
    union_members_vector->count = 0;
    union_members_vector->capacity = requested_size;

    return NO_ERROR;
}

Status reallocate_union_members_vector(UnionMembersVector *union_members_vector, size_t requested_size) {
    UnionMembers *temp = realloc(union_members_vector->array,sizeof(UnionMembers) * requested_size);
    if (temp == NULL) {
        return ALLOCATION_ERROR;
    }

    union_members_vector->array = temp;
    union_members_vector->capacity = requested_size;

    return NO_ERROR;
}

UnionMembersPointer insert_union_members(UnionMembersVector *union_members_vector,size_t offset, size_t size) {
    UnionMembersPointer returned_pointer = {0,NO_ERROR};

    if (union_members_vector->count + 1 >= union_members_vector->capacity) {
        Status reallocation_status = reallocate_union_members_vector(union_members_vector, union_members_vector->capacity*2);
        if (reallocation_status != NO_ERROR) {
            returned_pointer.status = reallocation_status;
            return returned_pointer;
        }
    }

    returned_pointer.index = union_members_vector->count;
    union_members_vector->array[union_members_vector->count].offset = offset;
    union_members_vector->array[union_members_vector->count].size = size;
    union_members_vector->count++;

    return returned_pointer;
}

Status free_union_members_vector(UnionMembersVector *union_members_vector) {
    if (union_members_vector->array == NULL || union_members_vector->capacity == 0 ) {
        return NULL_POINTER;
    }

    free(union_members_vector->array);
    union_members_vector->array = NULL;
    union_members_vector->capacity = 0;
    union_members_vector->count = 0;

    return NO_ERROR;
}
