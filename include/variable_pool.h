#ifndef VARIABLES_POOL_H
#define VARIABLES_POOL_H

#include "status.h"
#include <stddef.h>


typedef struct VariableDetails {
    size_t offset;
    size_t size;
} VariableDetails;

typedef struct VariablePool {
    VariableDetails *entries;
    size_t count;
    size_t capacity;
}VariablePool;

typedef struct VariableEntryPointer {
    size_t index;
    Status status;
}VariableEntryPointer;



#endif
