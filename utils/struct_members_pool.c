#include "struct_members_pool.h"
#include "status.h"
#include <stddef.h>
#include <stdlib.h>


Status allocate_struct_members(StructMembersPool *struct_members, size_t requested_size) {
    StructMembers *temp = malloc(sizeof(StructMembers) * requested_size);
    if (temp == NULL) {
        return ALLOCATION_ERROR;
    }

    struct_members->entries = temp;
    struct_members->count = 0;
    struct_members->capacity = requested_size;

    return NO_ERROR;
}

Status reallocate_struct_members(StructMembersPool *struct_members, size_t requested_size) {
    StructMembers *temp = realloc(struct_members->entries,sizeof(StructMembers) * requested_size);
    if (temp == NULL) {
        return ALLOCATION_ERROR;
    }

    struct_members->entries = temp;
    struct_members->capacity = requested_size;

    return NO_ERROR;
}

StructMembersPointer insert_struct_members(StructMembersPool *struct_members_pool,size_t offset, size_t size) {
    StructMembersPointer returned_pointer = {0,NO_ERROR};

    if (struct_members_pool->count + 1 >= struct_members_pool->capacity) {
        Status reallocation_status = reallocate_struct_members(struct_members_pool, struct_members_pool->capacity*2);
        if (reallocation_status != NO_ERROR) {
            returned_pointer.status = reallocation_status;
            return returned_pointer;
        }
    }

    returned_pointer.index = struct_members_pool->count;
    struct_members_pool->entries[struct_members_pool->count].offset = offset;
    struct_members_pool->entries[struct_members_pool->count].size = size;
    struct_members_pool->count++;

    return returned_pointer;
}

Status free_struct_members_pool(StructMembersPool *struct_members_pool) {
    if (struct_members_pool->entries == NULL || struct_members_pool->capacity == 0 ) {
        return NULL_POINTER;
    }

    free(struct_members_pool->entries);
    struct_members_pool->entries = NULL;
    struct_members_pool->capacity = 0;
    struct_members_pool->count = 0;

    return NO_ERROR;
}
