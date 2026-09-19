#ifndef FUNCTION_DETAILS_DYNAMIC_ARRAY_H
#define FUNCTION_DETAILS_DYNAMIC_ARRAY_H

#include "status.h"
#include <stddef.h>
#include <stdint.h>


typedef struct FunctionDetails {
    size_t code_offset;
    size_t return_size;
    size_t start_params_index;
    size_t param_count;
} FunctionDetails;

typedef struct FunctionDetailsDynamicArray {
    FunctionDetails *entries;
    size_t count;
    size_t capacity;
}FunctionDetailsDynamicArray;

typedef struct FunctionDetailsPointer {
    size_t index;
    Status status;
}FunctionDetailsPointer;



#endif
