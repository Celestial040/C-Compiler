#ifndef FUNCTION_PARAMS_VECTOR_H
#define FUNCTION_PARAMS_VECTOR_H

#include "../status.h"
#include <stddef.h>


typedef struct FunctionParams {
    size_t offset;
    size_t size;
} FunctionParams;

typedef struct FunctionParamsVector {
    FunctionParams *array;
    size_t count;
    size_t capacity;
}FunctionParamsVector;

typedef struct FunctionParamsPointer {
    size_t index;
    Status status;
}FunctionParamsPointer;



#endif
