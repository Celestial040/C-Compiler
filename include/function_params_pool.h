#ifndef FUNCTION_PARAMS_POOL_H
#define FUNCTION_PARAMS_POOL_H

#include "status.h"
#include <stddef.h>


typedef struct FunctionParams {
    size_t offset;
    size_t size;
} FunctionParams;

typedef struct FunctionParamsPool {
    FunctionParams *entries;
    size_t count;
    size_t capacity;
}FunctionParamsPool;

typedef struct FunctionParamsPointer {
    size_t index;
    Status status;
}FunctionParamsPointer;



#endif
