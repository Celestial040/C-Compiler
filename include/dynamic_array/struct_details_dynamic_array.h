#ifndef UNION_DETAILS_DYNAMIC_ARRAY_H
#define UNION_DETAILS_DYNAMIC_ARRAY_H

#include "status.h"
#include <stddef.h>
#include <stdint.h>


typedef struct StructDetails {
    size_t start_members_index;
    size_t member_count;
    size_t total_size;
} StructDetails;

typedef struct StructDetailsDynamicArray {
    StructDetails *entries;
    size_t count;
    size_t capacity;
}StructDetailsDynamicArray;

typedef struct StructDetailsPointer {
    size_t index;
    Status status;
}StructDetailsPointer;



#endif
