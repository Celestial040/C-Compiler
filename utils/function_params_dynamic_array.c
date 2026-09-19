#include "function_params_dynamic_array.h"
#include "status.h"
#include <stddef.h>
#include <stdlib.h>


Status allocate_function_params_dynamic_array(FunctionParamsDynamicArray *function_params_dynamic_array, size_t requested_size) {
    FunctionParams *temp = malloc(sizeof(FunctionParams) * requested_size);
    if (temp == NULL) {
        return ALLOCATION_ERROR;
    }

    function_params_dynamic_array->entries = temp;
    function_params_dynamic_array->count = 0;
    function_params_dynamic_array->capacity = requested_size;

    return NO_ERROR;
}

Status reallocate_function_params_dynamic_array(FunctionParamsDynamicArray *function_params_dynamic_array, size_t requested_size) {
    FunctionParams *temp = realloc(function_params_dynamic_array->entries,sizeof(FunctionParams) * requested_size);
    if (temp == NULL) {
        return ALLOCATION_ERROR;
    }

    function_params_dynamic_array->entries = temp;
    function_params_dynamic_array->capacity = requested_size;

    return NO_ERROR;
}

FunctionParamsPointer insert_params(FunctionParamsDynamicArray *function_params_dynamic_array,size_t offset, size_t size) {
    FunctionParamsPointer returned_pointer = {0,NO_ERROR};

    if (function_params_dynamic_array->count + 1 >= function_params_dynamic_array->capacity) {
        Status reallocation_status = reallocate_function_params_dynamic_array(function_params_dynamic_array, function_params_dynamic_array->capacity*2);
        if (reallocation_status != NO_ERROR) {
            returned_pointer.status = reallocation_status;
            return returned_pointer;
        }
    }

    returned_pointer.index = function_params_dynamic_array->count;
    function_params_dynamic_array->entries[function_params_dynamic_array->count].offset = offset;
    function_params_dynamic_array->entries[function_params_dynamic_array->count].size = size;
    function_params_dynamic_array->count++;

    return returned_pointer;
}

Status free_function_params_dynamic_array(FunctionParamsDynamicArray *function_params_dynamic_array) {
    if (function_params_dynamic_array->entries == NULL || function_params_dynamic_array->capacity == 0 ) {
        return NULL_POINTER;
    }

    free(function_params_dynamic_array->entries);
    function_params_dynamic_array->entries = NULL;
    function_params_dynamic_array->capacity = 0;
    function_params_dynamic_array->count = 0;

    return NO_ERROR;
}
