#include "vector/struct_members.h"
#include "status.h"
#include <stddef.h>
#include <stdlib.h>


Status allocate_struct_members_vector(StructMembersVector *struct_members_vector, size_t requested_size) {
    StructMembers *temp = malloc(sizeof(StructMembers) * requested_size);
    if (temp == NULL) {
        return ALLOCATION_ERROR;
    }

    struct_members_vector->array = temp;
    struct_members_vector->count = 0;
    struct_members_vector->capacity = requested_size;

    return NO_ERROR;
}

Status reallocate_struct_members_vector(StructMembersVector *struct_members_vector, size_t requested_size) {
    StructMembers *temp = realloc(struct_members_vector->array,sizeof(StructMembers) * requested_size);
    if (temp == NULL) {
        return ALLOCATION_ERROR;
    }

    struct_members_vector->array = temp;
    struct_members_vector->capacity = requested_size;

    return NO_ERROR;
}

StructMembersPointer insert_struct_members(StructMembersVector *struct_members_vector,size_t offset, size_t size) {
    StructMembersPointer returned_pointer = {0,NO_ERROR};

    if (struct_members_vector->count + 1 >= struct_members_vector->capacity) {
        Status reallocation_status = reallocate_struct_members_vector(struct_members_vector, struct_members_vector->capacity*2);
        if (reallocation_status != NO_ERROR) {
            returned_pointer.status = reallocation_status;
            return returned_pointer;
        }
    }

    returned_pointer.index = struct_members_vector->count;
    struct_members_vector->array[struct_members_vector->count].offset = offset;
    struct_members_vector->array[struct_members_vector->count].size = size;
    struct_members_vector->count++;

    return returned_pointer;
}

Status free_struct_members_vector(StructMembersVector *struct_members_vector) {
    if (struct_members_vector->array == NULL || struct_members_vector->capacity == 0 ) {
        return NULL_POINTER;
    }

    free(struct_members_vector->array);
    struct_members_vector->array = NULL;
    struct_members_vector->capacity = 0;
    struct_members_vector->count = 0;

    return NO_ERROR;
}
