#ifndef ENUM_MEMBERS_VECTOR_H
#define ENUM_MEMBERS_VECTOR_H

#include "../status.h"
#include <stddef.h>
#include <stdint.h>


typedef struct EnumMembers {
    size_t symbol_id;
    int64_t value;
} EnumMembers;

typedef struct EnumMembersVector {
    EnumMembers *array;
    size_t count;
    size_t capacity;
}EnumMembersVector;

typedef struct EnumMembersPointer {
    size_t index;
    Status status;
}EnumMembersPointer;



#endif
