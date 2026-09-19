#include "struct_members_dynamic_array.h"
#include "status.h"
#include <stddef.h>
#include <stdlib.h>


Status allocate_struct_members_dynamic_array(StructMembersDynamicArray *struct_members_dynamic_array, size_t requested_size) {
    StructMembers *temp = malloc(sizeof(StructMembers) * requested_size);
    if (temp == NULL) {
        return ALLOCATION_ERROR;
    }

    struct_members_dynamic_array->entries = temp;
    struct_members_dynamic_array->count = 0;
    struct_members_dynamic_array->capacity = requested_size;

    return NO_ERROR;
}

Status reallocate_struct_members_dynamic_array(StructMembersDynamicArray *struct_members_dynamic_array, size_t requested_size) {
    StructMembers *temp = realloc(struct_members_dynamic_array->entries,sizeof(StructMembers) * requested_size);
    if (temp == NULL) {
        return ALLOCATION_ERROR;
    }

    struct_members_dynamic_array->entries = temp;
    struct_members_dynamic_array->capacity = requested_size;

    return NO_ERROR;
}

StructMembersPointer insert_struct_members(StructMembersDynamicArray *struct_members_dynamic_array,size_t offset, size_t size) {
    StructMembersPointer returned_pointer = {0,NO_ERROR};

    if (struct_members_dynamic_array->count + 1 >= struct_members_dynamic_array->capacity) {
        Status reallocation_status = reallocate_struct_members_dynamic_array(struct_members_dynamic_array, struct_members_dynamic_array->capacity*2);
        if (reallocation_status != NO_ERROR) {
            returned_pointer.status = reallocation_status;
            return returned_pointer;
        }
    }

    returned_pointer.index = struct_members_dynamic_array->count;
    struct_members_dynamic_array->entries[struct_members_dynamic_array->count].offset = offset;
    struct_members_dynamic_array->entries[struct_members_dynamic_array->count].size = size;
    struct_members_dynamic_array->count++;

    return returned_pointer;
}

Status free_struct_members_dynamic_array(StructMembersDynamicArray *struct_members_dynamic_array) {
    if (struct_members_dynamic_array->entries == NULL || struct_members_dynamic_array->capacity == 0 ) {
        return NULL_POINTER;
    }

    free(struct_members_dynamic_array->entries);
    struct_members_dynamic_array->entries = NULL;
    struct_members_dynamic_array->capacity = 0;
    struct_members_dynamic_array->count = 0;

    return NO_ERROR;
}
