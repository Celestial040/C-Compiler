#ifndef STRUCT_MEMBERS_POOL_H
#define STRUCT_MEMBERS_POOL_H

#include "status.h"
#include <stddef.h>

typedef struct StructMembers {
    size_t offset;
    size_t size;
} StructMembers;

typedef struct StructMembersPool {
    StructMembers *entries;
    size_t count;
    size_t capacity;
}StructMembersPool;

typedef struct StructMembersPointer {
    size_t index;
    Status status;
}StructMembersPointer;

#endif
