#ifndef CHAR_MANIP_H
#define CHAR_MANIP_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef struct String {
    char *buffer;
    size_t length;
} String ;

static const char *numeric_literal_chars = "0123456789abcdeflpuxABCDEFLPUX.+-\0";
static const uint8_t numeric_literal_chars_len = 33;

static inline bool is_uppercase_alphabet(const char target) {return target >= 65 && target <= 90;}
static inline bool is_lowercase_alphabet(const char target) {return target >= 97 && target <= 122;}
static inline bool is_alphabet(const char target) {return is_uppercase_alphabet(target) || is_lowercase_alphabet(target);}
static inline bool is_numeric(const char target) {return target >= 48 && target <= 57;}
static inline bool is_alphabet_numeric(const char target) {return is_alphabet(target) || is_numeric(target);}
static inline bool is_whitespace(const char target) {return target == ' ' || (target >= '\t' && target <= '\r');}

static inline bool is_it_numeric_literal(const char target) {
    for (uint8_t i; i < numeric_literal_chars_len ; i++) {
        if (target == numeric_literal_chars[i]) {return true;}
    }
    return false;
}

#endif
