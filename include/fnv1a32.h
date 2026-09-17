#ifndef HASH_32_BIT_H
#define HASH_32_BIT_H

#include <stddef.h>
#include <stdint.h>

uint32_t fnv1a32(const char *data, size_t len);

#endif
