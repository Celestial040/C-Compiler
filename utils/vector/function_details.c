#include "vector/function_details.h"
#include "status.h"
#include <stddef.h>
#include <stdlib.h>


Status allocate_function_details_vector(FunctionDetailsVector *function_details_vector, size_t requested_size) {
    FunctionDetails *temp = malloc(sizeof(FunctionDetails) * requested_size);
    if (temp == NULL) {
        return ALLOCATION_ERROR;
    }

    function_details_vector->array = temp;
    function_details_vector->count = 0;
    function_details_vector->capacity = requested_size;

    return NO_ERROR;
}

Status reallocate_function_details_vector(FunctionDetailsVector *function_details_vector, size_t requested_size) {
    FunctionDetails *temp = realloc(function_details_vector->array,sizeof(FunctionDetails) * requested_size);
    if (temp == NULL) {
        return ALLOCATION_ERROR;
    }

    function_details_vector->array = temp;
    function_details_vector->capacity = requested_size;

    return NO_ERROR;
}

FunctionDetailsPointer insert_function_details(FunctionDetailsVector *function_details_vector, size_t param_count, size_t start_params_index, size_t code_offset, size_t return_size) {
    FunctionDetailsPointer returned_pointer = {0,NO_ERROR};

    if (function_details_vector->count + 1 >= function_details_vector->capacity) {
        Status reallocation_status = reallocate_function_details_vector(function_details_vector, function_details_vector->capacity*2);
        if (reallocation_status != NO_ERROR) {
            returned_pointer.status = reallocation_status;
            return returned_pointer;
        }
    }

    returned_pointer.index = function_details_vector->count;
    function_details_vector->array[function_details_vector->count].param_count = param_count;
    function_details_vector->array[function_details_vector->count].start_params_index = start_params_index;
    function_details_vector->array[function_details_vector->count].code_offset = code_offset;
    function_details_vector->array[function_details_vector->count].return_size = return_size;
    function_details_vector->count++;

    return returned_pointer;
}

Status function_details_vector(FunctionDetailsVector *function_details_vector) {
    if (function_details_vector->array == NULL || function_details_vector->capacity == 0 ) {
        return NULL_POINTER;
    }

    free(function_details_vector->array);
    function_details_vector->array = NULL;
    function_details_vector->capacity = 0;
    function_details_vector->count = 0;

    return NO_ERROR;
}
