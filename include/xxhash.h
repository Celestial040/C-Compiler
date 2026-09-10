#ifndef XXHASH_H
#define XXHASH_H

#include <stddef.h>
#include <stdint.h>

uint64_t xxh64(const void *data, size_t len, uint64_t seed);

#endif
