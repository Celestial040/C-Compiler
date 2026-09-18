#include "status.h"
#include "string_pool.h"
#include "test.h"
#include <stdlib.h>
#include <string.h>


TestStatusStruct test_string_pool() {

    TestStatusStruct test_status = {TEST_SUCCESS, "String Pool Test Success \n"};
    StringPool string_pool_test;
    Status allocation_status;
    StringPoolPointer insertion_status;

    const char *hello = "Hello";
    char *world = (char *) malloc(sizeof(char) * 6);
    const char *myname = "My name is yoshikage kira";


    allocation_status = allocate_string_pool(&string_pool_test, 8);

    if (allocation_status != NO_ERROR) {
        status_print(allocation_status);
        test_status.status = TEST_FAILED_RUNTIME_ERROR;
        test_status.message = "Runtime error\n";
    }

    if (string_pool_test.capacity != 8){
        test_status.status = TEST_FAILED_EXPECT_MISMATCH;
        test_status.message = "Allocation capacity isnt the right size\n";
        return test_status;
    }

    insertion_status = insert_string(&string_pool_test, "hello", 0);

    if (insertion_status.status != STRING_EMPTY) {
        test_status.status = TEST_FAILED_EXPECT_MISMATCH;
        test_status.message = "Empty string guard failed (1)\n";
        return test_status;
    }

    insertion_status = insert_string(&string_pool_test, "", 5);
    if (insertion_status.status != STRING_EMPTY) {
        test_status.status = TEST_FAILED_EXPECT_MISMATCH;
        test_status.message = "Empty string guard failed (2)\n";
        return test_status;
    }

    insertion_status = insert_string(&string_pool_test, hello, 5);
    if (string_pool_test.used != 5+1 || memcmp(string_pool_test.start_pointer, hello, 5) != 0) {
        test_status.status = TEST_FAILED_EXPECT_MISMATCH;
        test_status.message = "Insertion doesnt give the expected value (1)\n";
        return test_status;
    }

    if (string_pool_test.start_pointer[string_pool_test.used] != '\0') {
        test_status.status = TEST_FAILED_EXPECT_MISMATCH;
        test_status.message = "You forgot to insert null terminator (1)\n";
        return test_status;
    }

    hello = NULL;

    if (string_pool_test.used != 5+1 || memcmp(string_pool_test.start_pointer, "Hello", 5) != 0) {
        test_status.status = TEST_FAILED_EXPECT_MISMATCH;
        test_status.message = "The memory isnt persistent (1)\n";
        return test_status;
    }

    insertion_status = insert_string(&string_pool_test, world, 5);
    if (insertion_status.status != STRING_EMPTY) {
        test_status.status = TEST_FAILED_EXPECT_MISMATCH;
        test_status.message = "Empty string guard failed (3)\n";
        return test_status;
    }

    memcpy(world, "world", 6);
    world[6] = '\0';
    insertion_status = insert_string(&string_pool_test, world, 5);

    if (string_pool_test.used != 5+1+5+1 || memcmp(string_pool_test.start_pointer + 5 + 1, world, 5) != 0) {
        test_status.status = TEST_FAILED_EXPECT_MISMATCH;
        test_status.message = "Insertion doesnt give the expected value (2)\n";
        return test_status;
    }

    if (string_pool_test.start_pointer[string_pool_test.used] != '\0') {
        test_status.status = TEST_FAILED_EXPECT_MISMATCH;
        test_status.message = "You forgot to insert null terminator (1)\n";
        return test_status;
    }

    if (string_pool_test.capacity != 16){
        test_status.status = TEST_FAILED_EXPECT_MISMATCH;
        test_status.message = "Reallocation size isnt the same as expected (1)\n";
        return test_status;
    }

    free(world);
    world = NULL;

    if (string_pool_test.used != 5+1+5+1 || memcmp(string_pool_test.start_pointer + 5 + 1, "world", 5) != 0){
        test_status.status = TEST_FAILED_EXPECT_MISMATCH;
        test_status.message = "The memory isnt persistent (2)\n";
        return test_status;
    }

    insertion_status = insert_string(&string_pool_test, myname, 25);

    if (insertion_status.status != NO_ERROR) {
        status_print(insertion_status.status);
        test_status.status = TEST_FAILED_RUNTIME_ERROR;
        test_status.message = "Runtime error\n";
    }

    if (string_pool_test.used != 5+1+5+1+25+1 || memcmp(string_pool_test.start_pointer + 5+1+5+1, myname, 25) != 0){
        test_status.status = TEST_FAILED_EXPECT_MISMATCH;
        test_status.message = "Insertion doesnt give the expected value (3)\n";
        return test_status;
    }

    if (string_pool_test.start_pointer[string_pool_test.used] != '\0') {
        test_status.status = TEST_FAILED_EXPECT_MISMATCH;
        test_status.message = "You forgot to insert null terminator (2)";
        return test_status;
    }

    if (string_pool_test.capacity != 32){
        test_status.status = TEST_FAILED_EXPECT_MISMATCH;
        test_status.message = "Reallocation size isnt the same as expected (2)\n";
        return test_status;
    }

    free_string_pool(&string_pool_test);
    if (string_pool_test.start_pointer !=  NULL || string_pool_test.capacity != 0 || string_pool_test.used != 0) {
        test_status.status = TEST_FAILED_EXPECT_MISMATCH;
        test_status.message = "String pool not freed correctly";
        return test_status;
    }

    return test_status;
}
