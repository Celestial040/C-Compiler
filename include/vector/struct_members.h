#ifndef STRUCT_MEMBERS_VECTOR_H
#define STRUCT_MEMBERS_VECTOR_H

#include "../status.h"
#include <stddef.h>

typedef struct StructMembers {
    size_t offset;
    size_t size;
} StructMembers;

typedef struct StructMembersVector{
    StructMembers *array;
    size_t count;
    size_t capacity;
}StructMembersVector;

typedef struct StructMembersPointer {
    size_t index;
    Status status;
}StructMembersPointer;

#endif
