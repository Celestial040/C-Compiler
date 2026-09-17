#ifndef TEST_SUITE_H
#define TEST_SUITE_H

#include "status.h"
#include <stddef.h>
#include <stdio.h>

typedef enum TestStatus {
    TEST_SUCCESS,
    TEST_FAILED_EXPECT_MISMATCH,
    TEST_FAILED_RUNTIME_ERROR
} TestStatus ;


typedef struct TestStatusStruct {
    TestStatus status;
    const char *message;
} TestStatusStruct;


static inline void print_test_status(TestStatusStruct result) {
    printf("%s",result.message);
}


TestStatusStruct test_string_pool();
TestStatusStruct test_symbol_pool();
TestStatusStruct test_tokens_hashmap();
Status runtime_exec();
#endif
