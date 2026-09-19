#ifndef VARIABLE_LIST_H
#define VARIABLE_LIST_H

#include <stddef.h>
#include <stdint.h>

typedef struct FunctionDetails {
    size_t code_offset;
    size_t return_size;
    size_t start_params_index;
    size_t param_count;
} FunctionDetails;

typedef struct StructDetails {
    size_t start_members_index;
    size_t member_count;
    size_t total_size;
} StructDetails;

typedef struct EnumMembers {
    size_t symbol_id;
    int64_t value;
} EnumMembers;

typedef struct EnumDetails {
    size_t start_members_index;
    size_t member_count;
} EnumDetails;

typedef struct UnionMembers {
    size_t offset;
    size_t size;
} UnionMembers;

typedef struct UnionDetails {
    size_t start_members_index;
    size_t member_count;
    size_t total_size;
} UnionDetails;

typedef struct TypeAliasDetails {
    size_t aliased_symbol_id;
    size_t size;
} TypeAliasDetails;


#endif
