#include "dynamic_array/union_members_dynamic_array.h"
#include "status.h"
#include <stddef.h>
#include <stdlib.h>


Status allocate_union_members_dynamic_array(UnionMembersDynamicArray *union_members_dynamic_array, size_t requested_size) {
    UnionMembers *temp = malloc(sizeof(UnionMembers) * requested_size);
    if (temp == NULL) {
        return ALLOCATION_ERROR;
    }

    union_members_dynamic_array->entries = temp;
    union_members_dynamic_array->count = 0;
    union_members_dynamic_array->capacity = requested_size;

    return NO_ERROR;
}

Status reallocate_union_members_dynamic_array(UnionMembersDynamicArray *union_members_dynamic_array, size_t requested_size) {
    UnionMembers *temp = realloc(union_members_dynamic_array->entries,sizeof(UnionMembers) * requested_size);
    if (temp == NULL) {
        return ALLOCATION_ERROR;
    }

    union_members_dynamic_array->entries = temp;
    union_members_dynamic_array->capacity = requested_size;

    return NO_ERROR;
}

UnionMembersPointer insert_union_members(UnionMembersDynamicArray *union_members_dynamic_array,size_t offset, size_t size) {
    UnionMembersPointer returned_pointer = {0,NO_ERROR};

    if (union_members_dynamic_array->count + 1 >= union_members_dynamic_array->capacity) {
        Status reallocation_status = reallocate_union_members_dynamic_array(union_members_dynamic_array, union_members_dynamic_array->capacity*2);
        if (reallocation_status != NO_ERROR) {
            returned_pointer.status = reallocation_status;
            return returned_pointer;
        }
    }

    returned_pointer.index = union_members_dynamic_array->count;
    union_members_dynamic_array->entries[union_members_dynamic_array->count].offset = offset;
    union_members_dynamic_array->entries[union_members_dynamic_array->count].size = size;
    union_members_dynamic_array->count++;

    return returned_pointer;
}

Status free_union_members_dynamic_array(UnionMembersDynamicArray *union_members_dynamic_array) {
    if (union_members_dynamic_array->entries == NULL || union_members_dynamic_array->capacity == 0 ) {
        return NULL_POINTER;
    }

    free(union_members_dynamic_array->entries);
    union_members_dynamic_array->entries = NULL;
    union_members_dynamic_array->capacity = 0;
    union_members_dynamic_array->count = 0;

    return NO_ERROR;
}
