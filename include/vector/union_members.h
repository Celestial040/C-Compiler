#ifndef UNION_MEMBERS_VECTOR_H
#define UNION_MEMBERS_VECTOR_H

#include "../status.h"
#include <stddef.h>
#include <stdint.h>


typedef struct UnionMembers {
    size_t offset;
    size_t size;
} UnionMembers;

typedef struct UnionMembersVector {
    UnionMembers *array;
    size_t count;
    size_t capacity;
}UnionMembersVector;

typedef struct UnionMembersPointer {
    size_t index;
    Status status;
}UnionMembersPointer;



#endif
