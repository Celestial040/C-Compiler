#ifndef STRING_POOL_H
#define STRING_POOL_H

#include "status.h"
#include <stddef.h>

typedef struct StringPool {
    char *start_pointer;
    size_t used;
    size_t capacity;
}
StringPool;

typedef struct StringPoolPointer {
    size_t string_start;
    size_t string_length;
    Status status;
}StringPoolPointer;


Status allocate_string_pool(StringPool *string_pool, size_t size_requested);
StringPoolPointer insert_string(StringPool *string_pool, const char *string, const size_t string_len);

#endif
