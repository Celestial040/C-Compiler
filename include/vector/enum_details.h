#ifndef ENUM_DETAILS_VECTOR_H
#define ENUM_DETAILS_VECTOR_H

#include "../status.h"
#include <stddef.h>
#include <stdint.h>


typedef struct EnumDetails {
    size_t start_members_index;
    size_t member_count;
} EnumDetails;

typedef struct EnumDetailsVector {
    EnumDetails *array;
    size_t count;
    size_t capacity;
}EnumDetailsVector;

typedef struct EnumDetailsPointer {
    size_t index;
    Status status;
}EnumDetailsPointer;



#endif
