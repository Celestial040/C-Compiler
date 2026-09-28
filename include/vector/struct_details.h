#ifndef UNION_DETAILS_VECTOR_H
#define UNION_DETAILS_VECTOR_H

#include "../status.h"
#include <stddef.h>
#include <stdint.h>


typedef struct StructDetails {
    size_t start_members_index;
    size_t member_count;
    size_t total_size;
} StructDetails;

typedef struct StructDetailsVector {
    StructDetails *array;
    size_t count;
    size_t capacity;
}StructDetailsVector;

typedef struct StructDetailsPointer {
    size_t index;
    Status status;
}StructDetailsPointer;



#endif
