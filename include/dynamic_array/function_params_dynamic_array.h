#ifndef FUNCTION_PARAMS_DYNAMIC_ARRAY_H
#define FUNCTION_PARAMS_DYNAMIC_ARRAY_H

#include "status.h"
#include <stddef.h>


typedef struct FunctionParams {
    size_t offset;
    size_t size;
} FunctionParams;

typedef struct FunctionParamsDynamicArray {
    FunctionParams *entries;
    size_t count;
    size_t capacity;
}FunctionParamsDynamicArray;

typedef struct FunctionParamsPointer {
    size_t index;
    Status status;
}FunctionParamsPointer;



#endif
