#ifndef VARIABLES_DYNAMIC_ARRAY_H
#define VARIABLES_DYNAMIC_ARRAY_H

#include "status.h"
#include <stddef.h>

typedef struct VariableDetails {
    size_t offset;
    size_t size;
} VariableDetails;

typedef struct VariableDynamicArray {
    VariableDetails *entries;
    size_t count;
    size_t capacity;
}VariableDynamicArray;

typedef struct VariableEntryPointer {
    size_t index;
    Status status;
}VariableEntryPointer;

#endif
