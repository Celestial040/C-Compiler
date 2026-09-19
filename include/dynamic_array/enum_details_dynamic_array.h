#ifndef ENUM_DETAILS_DYNAMIC_ARRAY_H
#define ENUM_DETAILS_DYNAMIC_ARRAY_H

#include "status.h"
#include <stddef.h>
#include <stdint.h>


typedef struct EnumDetails {
    size_t start_members_index;
    size_t member_count;
} EnumDetails;

typedef struct EnumDetailsDynamicArray {
    EnumDetails *entries;
    size_t count;
    size_t capacity;
}EnumDetailsDynamicArray;

typedef struct EnumDetailsPointer {
    size_t index;
    Status status;
}EnumDetailsPointer;



#endif
