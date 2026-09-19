#ifndef UNION_DETAILS_DYNAMIC_ARRAY_H
#define UNION_DETAILS_DYNAMIC_ARRAY_H

#include "status.h"
#include <stddef.h>
#include <stdint.h>


typedef struct UnionDetails {
    size_t start_members_index;
    size_t member_count;
    size_t total_size;
} UnionDetails;

typedef struct UnionDetailsDynamicArray {
    UnionDetails *entries;
    size_t count;
    size_t capacity;
}UnionDetailsDynamicArray;

typedef struct UnionDetailsPointer {
    size_t index;
    Status status;
}UnionDetailsPointer;



#endif
