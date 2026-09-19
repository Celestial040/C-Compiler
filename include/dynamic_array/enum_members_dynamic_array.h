#ifndef ENUM_MEMBERS_DYNAMIC_ARRAY_H
#define ENUM_MEMBERS_DYNAMIC_ARRAY_H

#include "status.h"
#include <stddef.h>
#include <stdint.h>


typedef struct EnumMembers {
    size_t symbol_id;
    int64_t value;
} EnumMembers;

typedef struct EnumMembersDynamicArray {
    EnumMembers *entries;
    size_t count;
    size_t capacity;
}EnumMembersDynamicArray;

typedef struct EnumMembersPointer {
    size_t index;
    Status status;
}EnumMembersPointer;



#endif
