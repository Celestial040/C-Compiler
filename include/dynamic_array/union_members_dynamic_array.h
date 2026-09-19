#ifndef UNION_MEMBERS_DYNAMIC_ARRAY_H
#define UNION_MEMBERS_DYNAMIC_ARRAY_H

#include "status.h"
#include <stddef.h>
#include <stdint.h>


typedef struct UnionMembers {
    size_t offset;
    size_t size;
} UnionMembers;

typedef struct UnionMembersDynamicArray {
    UnionMembers *entries;
    size_t count;
    size_t capacity;
}UnionMembersDynamicArray;

typedef struct UnionMembersPointer {
    size_t index;
    Status status;
}UnionMembersPointer;



#endif
