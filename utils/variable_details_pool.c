#include "status.h"
#include "variable_pool.h"
#include <stddef.h>
#include <stdlib.h>


Status allocate_variable_details_pool(VariablePool *variables_pool, size_t requested_size) {
    VariableDetails *temp = malloc(sizeof(VariableDetails) * requested_size);
    if (temp == NULL) {
        return ALLOCATION_ERROR;
    }

    variables_pool->entries = temp;
    variables_pool->count = 0;
    variables_pool->capacity = requested_size;

    return NO_ERROR;
}

Status reallocate_variable_details_pool(VariablePool *variable_pool, size_t requested_size) {
    VariableDetails *temp = realloc(variable_pool->entries,sizeof(VariableDetails) * requested_size);
    if (temp == NULL) {
        return ALLOCATION_ERROR;
    }

    variable_pool->entries = temp;
    variable_pool->capacity = requested_size;

    return NO_ERROR;
}

VariableEntryPointer insert_variable(VariablePool *variable_pool,size_t offset, size_t size) {
    VariableEntryPointer returned_pointer = {0,NO_ERROR};

    if (variable_pool->count + 1 >= variable_pool->capacity) {
        Status reallocation_status = reallocate_variable_details_pool(variable_pool, variable_pool->capacity*2);
        if (reallocation_status != NO_ERROR) {
            returned_pointer.status = reallocation_status;
            return returned_pointer;
        }
    }

    returned_pointer.index = variable_pool->count;
    variable_pool->entries[variable_pool->count].offset = offset;
    variable_pool->entries[variable_pool->count].size = size;
    variable_pool->count++;

    return returned_pointer;
}

Status free_variable_pool(VariablePool *variable_pool) {
    if (variable_pool->entries == NULL || variable_pool->capacity == 0 ) {
        return NULL_POINTER;
    }

    free(variable_pool->entries);
    variable_pool->entries = NULL;
    variable_pool->capacity = 0;
    variable_pool->count = 0;

    return NO_ERROR;
}
