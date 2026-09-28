#ifndef VARIABLES_VECTOR_H
#define VARIABLES_VECTOR_H

#include "../status.h"
#include <stddef.h>

typedef struct VariableDetails {
    size_t offset;
    size_t size;
} VariableDetails;

typedef struct VariableVector {
    VariableDetails *array;
    size_t count;
    size_t capacity;
}VariableVector;

typedef struct VariableEntryPointer {
    size_t index;
    Status status;
}VariableEntryPointer;

#endif
