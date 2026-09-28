#ifndef UNION_DETAILS_VECTOR_H
#define UNION_DETAILS_VECTOR_H

#include "../status.h"
#include <stddef.h>
#include <stdint.h>


typedef struct UnionDetails {
    size_t start_members_index;
    size_t member_count;
    size_t total_size;
} UnionDetails;

typedef struct UnionDetailsVector {
    UnionDetails *array;
    size_t count;
    size_t capacity;
}UnionDetailsVector;

typedef struct UnionDetailsPointer {
    size_t index;
    Status status;
}UnionDetailsPointer;

#endif
