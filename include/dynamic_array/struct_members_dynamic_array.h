#ifndef STRUCT_MEMBERS_DYNAMIC_ARRAY_H
#define STRUCT_MEMBERS_DYNAMIC_ARRAY_H

#include "status.h"
#include <stddef.h>

typedef struct StructMembers {
    size_t offset;
    size_t size;
} StructMembers;

typedef struct StructMembersDynamicArray{
    StructMembers *entries;
    size_t count;
    size_t capacity;
}StructMembersDynamicArray;

typedef struct StructMembersPointer {
    size_t index;
    Status status;
}StructMembersPointer;

#endif
