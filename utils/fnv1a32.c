#include <stddef.h>
#include <stdint.h>

uint32_t fnv1a32(const char *data, size_t len) {
    const uint8_t *p = (const uint8_t *)data;
    uint32_t hash = 2166136261u;
    size_t i;
    for (i = 0; i < len; i++) {
        hash ^= p[i];
        hash *= 16777619u;
    }
    return hash;
}
