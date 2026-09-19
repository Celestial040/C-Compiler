#include "function_params_pool.h"
#include "status.h"
#include <stddef.h>
#include <stdlib.h>


Status allocate_function_params_pool(FunctionParamsPool *function_params_pool, size_t requested_size) {
    FunctionParams *temp = malloc(sizeof(FunctionParams) * requested_size);
    if (temp == NULL) {
        return ALLOCATION_ERROR;
    }

    function_params_pool->entries = temp;
    function_params_pool->count = 0;
    function_params_pool->capacity = requested_size;

    return NO_ERROR;
}

Status reallocate_function_params_pool(FunctionParamsPool *function_params_pool, size_t requested_size) {
    FunctionParams *temp = realloc(function_params_pool->entries,sizeof(FunctionParams) * requested_size);
    if (temp == NULL) {
        return ALLOCATION_ERROR;
    }

    function_params_pool->entries = temp;
    function_params_pool->capacity = requested_size;

    return NO_ERROR;
}

FunctionParamsPointer insert_params(FunctionParamsPool *function_params_pool,size_t offset, size_t size) {
    FunctionParamsPointer returned_pointer = {0,NO_ERROR};

    if (function_params_pool->count + 1 >= function_params_pool->capacity) {
        Status reallocation_status = reallocate_function_params_pool(function_params_pool, function_params_pool->capacity*2);
        if (reallocation_status != NO_ERROR) {
            returned_pointer.status = reallocation_status;
            return returned_pointer;
        }
    }

    returned_pointer.index = function_params_pool->count;
    function_params_pool->entries[function_params_pool->count].offset = offset;
    function_params_pool->entries[function_params_pool->count].size = size;
    function_params_pool->count++;

    return returned_pointer;
}

Status free_function_params_pool(FunctionParamsPool *function_params_pool) {
    if (function_params_pool->entries == NULL || function_params_pool->capacity == 0 ) {
        return NULL_POINTER;
    }

    free(function_params_pool->entries);
    function_params_pool->entries = NULL;
    function_params_pool->capacity = 0;
    function_params_pool->count = 0;

    return NO_ERROR;
}
