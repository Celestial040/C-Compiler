#include <stdint.h>
#include <string.h>

static const uint64_t P1 = 0x9E3779B185EBCA87ULL;
static const uint64_t P2 = 0xC2B2AE3D27D4EB4FULL;
static const uint64_t P3 = 0x165667B19E3779F9ULL;
static const uint64_t P4 = 0x85EBCA77C2B2AE63ULL;
static const uint64_t P5 = 0x27D4EB2F165667C5ULL;

static uint64_t rotl64(uint64_t x, int r) {
    return (x << r) | (x >> (64 - r));
}

static uint64_t round64(uint64_t acc, uint64_t input) {
    acc += input * P2;
    acc = rotl64(acc, 31);
    acc *= P1;
    return acc;
}

uint64_t xxh64(const void *data, size_t len, uint64_t seed) {
    const uint8_t *p = (const uint8_t *)data;
    const uint8_t *end = p + len;
    uint64_t h64;

    if (len >= 32) {
        const uint8_t *limit = end - 32;
        uint64_t v1 = seed + P1 + P2;
        uint64_t v2 = seed + P2;
        uint64_t v3 = seed;
        uint64_t v4 = seed - P1;

        do {
            uint64_t k1, k2, k3, k4;
            memcpy(&k1, p, 8); p += 8;
            memcpy(&k2, p, 8); p += 8;
            memcpy(&k3, p, 8); p += 8;
            memcpy(&k4, p, 8); p += 8;

            v1 = round64(v1, k1);
            v2 = round64(v2, k2);
            v3 = round64(v3, k3);
            v4 = round64(v4, k4);
        } while (p <= limit);

        h64 = rotl64(v1, 1) + rotl64(v2, 7) + rotl64(v3, 12) + rotl64(v4, 18);

        v1 = round64(0, v1); h64 ^= v1; h64 = h64 * P1 + P4;
        v2 = round64(0, v2); h64 ^= v2; h64 = h64 * P1 + P4;
        v3 = round64(0, v3); h64 ^= v3; h64 = h64 * P1 + P4;
        v4 = round64(0, v4); h64 ^= v4; h64 = h64 * P1 + P4;
    } else {
        h64 = seed + P5;
    }

    h64 += (uint64_t)len;

    while (p + 8 <= end) {
        uint64_t k1;
        memcpy(&k1, p, 8);
        k1 = round64(0, k1);
        h64 ^= k1;
        h64 = rotl64(h64, 27) * P1 + P4;
        p += 8;
    }

    if (p + 4 <= end) {
        uint32_t k1;
        memcpy(&k1, p, 4);
        h64 ^= (uint64_t)k1 * P1;
        h64 = rotl64(h64, 23) * P2 + P3;
        p += 4;
    }

    while (p < end) {
        h64 ^= (*p) * P5;
        h64 = rotl64(h64, 11) * P1;
        p++;
    }

    h64 ^= h64 >> 33;
    h64 *= P2;
    h64 ^= h64 >> 29;
    h64 *= P3;
    h64 ^= h64 >> 32;

    return h64;
}
