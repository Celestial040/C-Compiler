#include "vector/function_params.h"
#include "status.h"
#include <stddef.h>
#include <stdlib.h>


Status allocate_function_params_vector(FunctionParamsVector *function_params_vector, size_t requested_size) {
    FunctionParams *temp = malloc(sizeof(FunctionParams) * requested_size);
    if (temp == NULL) {
        return ALLOCATION_ERROR;
    }

    function_params_vector->array = temp;
    function_params_vector->count = 0;
    function_params_vector->capacity = requested_size;

    return NO_ERROR;
}

Status reallocate_function_params_vector(FunctionParamsVector *function_params_vector, size_t requested_size) {
    FunctionParams *temp = realloc(function_params_vector->array,sizeof(FunctionParams) * requested_size);
    if (temp == NULL) {
        return ALLOCATION_ERROR;
    }

    function_params_vector->array = temp;
    function_params_vector->capacity = requested_size;

    return NO_ERROR;
}

FunctionParamsPointer insert_params(FunctionParamsVector *function_params_vector,size_t offset, size_t size) {
    FunctionParamsPointer returned_pointer = {0,NO_ERROR};

    if (function_params_vector->count + 1 >= function_params_vector->capacity) {
        Status reallocation_status = reallocate_function_params_vector(function_params_vector, function_params_vector->capacity*2);
        if (reallocation_status != NO_ERROR) {
            returned_pointer.status = reallocation_status;
            return returned_pointer;
        }
    }

    returned_pointer.index = function_params_vector->count;
    function_params_vector->array[function_params_vector->count].offset = offset;
    function_params_vector->array[function_params_vector->count].size = size;
    function_params_vector->count++;

    return returned_pointer;
}

Status free_function_params_vector(FunctionParamsVector *function_params_vector) {
    if (function_params_vector->array == NULL || function_params_vector->capacity == 0 ) {
        return NULL_POINTER;
    }

    free(function_params_vector->array);
    function_params_vector->array = NULL;
    function_params_vector->capacity = 0;
    function_params_vector->count = 0;

    return NO_ERROR;
}
