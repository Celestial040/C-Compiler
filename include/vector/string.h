#ifndef STRING_VECTOR_H
#define STRING_VECTOR_H

#include "../status.h"
#include <stddef.h>

typedef struct StringVector {
    char *start_pointer;
    size_t used;
    size_t capacity;
}StringVector;

typedef struct StringVectorPointer {
    size_t string_start;
    size_t string_length;
    Status status;
}StringVectorPointer;


Status allocate_string_vector(StringVector *string_vector, size_t size_requested);
StringVectorPointer insert_string(StringVector *string_vector, const char *string, const size_t string_len);
Status free_string_vector(StringVector *string_vector);

#endif
