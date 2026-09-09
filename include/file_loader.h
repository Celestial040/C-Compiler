#ifndef FILE_LOADER
#define FILE_LOADER

#include "status.h"

typedef struct FileString {
    char *start;
    size_t length;
} FileString;

Status read_file(const char *filename, FileString *output);

#endif
