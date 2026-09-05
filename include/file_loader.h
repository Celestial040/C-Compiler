#ifndef FILE_LOADER
#define FILE_LOADER

#include "status.h"

typedef struct FileString {
    char *start;
    size_t length;
} Filestring;

Status read_file(const char *filename, Filestring *output);

#endif
