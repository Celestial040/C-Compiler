#include "status.h"
#include "variable_dynamic_array.h"
#include <stddef.h>
#include <stdlib.h>


Status allocate_variable_details_dynamic_array(VariableDynamicArray *variables_dynamic_array, size_t requested_size) {
    VariableDetails *temp = malloc(sizeof(VariableDetails) * requested_size);
    if (temp == NULL) {
        return ALLOCATION_ERROR;
    }

    variables_dynamic_array->entries = temp;
    variables_dynamic_array->count = 0;
    variables_dynamic_array->capacity = requested_size;

    return NO_ERROR;
}

Status reallocate_variable_details_dynamic_array(VariableDynamicArray *variable_dynamic_array, size_t requested_size) {
    VariableDetails *temp = realloc(variable_dynamic_array->entries,sizeof(VariableDetails) * requested_size);
    if (temp == NULL) {
        return ALLOCATION_ERROR;
    }

    variable_dynamic_array->entries = temp;
    variable_dynamic_array->capacity = requested_size;

    return NO_ERROR;
}

VariableEntryPointer insert_variable(VariableDynamicArray *variable_dynamic_array,size_t offset, size_t size) {
    VariableEntryPointer returned_pointer = {0,NO_ERROR};

    if (variable_dynamic_array->count + 1 >= variable_dynamic_array->capacity) {
        Status reallocation_status = reallocate_variable_details_dynamic_array(variable_dynamic_array, variable_dynamic_array->capacity*2);
        if (reallocation_status != NO_ERROR) {
            returned_pointer.status = reallocation_status;
            return returned_pointer;
        }
    }

    returned_pointer.index = variable_dynamic_array->count;
    variable_dynamic_array->entries[variable_dynamic_array->count].offset = offset;
    variable_dynamic_array->entries[variable_dynamic_array->count].size = size;
    variable_dynamic_array->count++;

    return returned_pointer;
}

Status free_variable_dynamic_array(VariableDynamicArray *variable_dynamic_array) {
    if (variable_dynamic_array->entries == NULL || variable_dynamic_array->capacity == 0 ) {
        return NULL_POINTER;
    }

    free(variable_dynamic_array->entries);
    variable_dynamic_array->entries = NULL;
    variable_dynamic_array->capacity = 0;
    variable_dynamic_array->count = 0;

    return NO_ERROR;
}
