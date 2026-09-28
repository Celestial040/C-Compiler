#include "status.h"
#include "vector/variable.h"
#include <stddef.h>
#include <stdlib.h>


Status allocate_variable_details_vector(VariableVector *variables_vector, size_t requested_size) {
    VariableDetails *temp = malloc(sizeof(VariableDetails) * requested_size);
    if (temp == NULL) {
        return ALLOCATION_ERROR;
    }

    variables_vector->array = temp;
    variables_vector->count = 0;
    variables_vector->capacity = requested_size;

    return NO_ERROR;
}

Status reallocate_variable_details_vector(VariableVector *variable_vector, size_t requested_size) {
    VariableDetails *temp = realloc(variable_vector->array,sizeof(VariableDetails) * requested_size);
    if (temp == NULL) {
        return ALLOCATION_ERROR;
    }

    variable_vector->array = temp;
    variable_vector->capacity = requested_size;

    return NO_ERROR;
}

VariableEntryPointer insert_variable(VariableVector *variable_vector,size_t offset, size_t size) {
    VariableEntryPointer returned_pointer = {0,NO_ERROR};

    if (variable_vector->count + 1 >= variable_vector->capacity) {
        Status reallocation_status = reallocate_variable_details_vector(variable_vector, variable_vector->capacity*2);
        if (reallocation_status != NO_ERROR) {
            returned_pointer.status = reallocation_status;
            return returned_pointer;
        }
    }

    returned_pointer.index = variable_vector->count;
    variable_vector->array[variable_vector->count].offset = offset;
    variable_vector->array[variable_vector->count].size = size;
    variable_vector->count++;

    return returned_pointer;
}

Status free_variable_vector(VariableVector *variable_vector) {
    if (variable_vector->array == NULL || variable_vector->capacity == 0 ) {
        return NULL_POINTER;
    }

    free(variable_vector->array);
    variable_vector->array = NULL;
    variable_vector->capacity = 0;
    variable_vector->count = 0;

    return NO_ERROR;
}
