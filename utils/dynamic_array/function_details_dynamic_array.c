#include "dynamic_array/function_details_dynamic_array.h"
#include "status.h"
#include <stddef.h>
#include <stdlib.h>


Status allocate_function_details_dynamic_array(FunctionDetailsDynamicArray *function_details_dynamic_array, size_t requested_size) {
    FunctionDetails *temp = malloc(sizeof(FunctionDetails) * requested_size);
    if (temp == NULL) {
        return ALLOCATION_ERROR;
    }

    function_details_dynamic_array->entries = temp;
    function_details_dynamic_array->count = 0;
    function_details_dynamic_array->capacity = requested_size;

    return NO_ERROR;
}

Status reallocate_function_details_dynamic_array(FunctionDetailsDynamicArray *function_details_dynamic_array, size_t requested_size) {
    FunctionDetails *temp = realloc(function_details_dynamic_array->entries,sizeof(FunctionDetails) * requested_size);
    if (temp == NULL) {
        return ALLOCATION_ERROR;
    }

    function_details_dynamic_array->entries = temp;
    function_details_dynamic_array->capacity = requested_size;

    return NO_ERROR;
}

FunctionDetailsPointer insert_function_details(FunctionDetailsDynamicArray *function_details_dynamic_array, size_t param_count, size_t start_params_index, size_t code_offset, size_t return_size) {
    FunctionDetailsPointer returned_pointer = {0,NO_ERROR};

    if (function_details_dynamic_array->count + 1 >= function_details_dynamic_array->capacity) {
        Status reallocation_status = reallocate_function_details_dynamic_array(function_details_dynamic_array, function_details_dynamic_array->capacity*2);
        if (reallocation_status != NO_ERROR) {
            returned_pointer.status = reallocation_status;
            return returned_pointer;
        }
    }

    returned_pointer.index = function_details_dynamic_array->count;
    function_details_dynamic_array->entries[function_details_dynamic_array->count].param_count = param_count;
    function_details_dynamic_array->entries[function_details_dynamic_array->count].start_params_index = start_params_index;
    function_details_dynamic_array->entries[function_details_dynamic_array->count].code_offset = code_offset;
    function_details_dynamic_array->entries[function_details_dynamic_array->count].return_size = return_size;
    function_details_dynamic_array->count++;

    return returned_pointer;
}

Status function_details_dynamic_array(FunctionDetailsDynamicArray *function_details_dynamic_array) {
    if (function_details_dynamic_array->entries == NULL || function_details_dynamic_array->capacity == 0 ) {
        return NULL_POINTER;
    }

    free(function_details_dynamic_array->entries);
    function_details_dynamic_array->entries = NULL;
    function_details_dynamic_array->capacity = 0;
    function_details_dynamic_array->count = 0;

    return NO_ERROR;
}
