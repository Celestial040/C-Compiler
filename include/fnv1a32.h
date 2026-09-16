#ifndef HASH_32_BIT_H
#define HASH_32_BIT_H

#include <stddef.h>
#include <stdint.h>

static inline uint32_t fnv1a32(const char *data, size_t len) {
    const uint8_t *p = (const uint8_t *)data;
    uint32_t hash = 2166136261u;
    for (size_t i = 0; i < len; i++) {
        hash ^= p[i];
        hash *= 16777619u;
    }
    return hash;
}

#endif
