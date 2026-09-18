#include "status.h"
#include "string_pool.h"
#include "symbol_pool.h"
#include "test.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>

TestStatusStruct test_symbol_pool() {

    TestStatusStruct test_status = {TEST_SUCCESS, "Symbol Pool Test Success \n"};
    Status allocation_status;

    StringPool string_pool_test;
    SymbolPool symbol_pool_test;

    SymbolEntry created_entry;

    Semantic test_token = {TOKEN_KEYWORD, INT, SYMBOL_KEYWORD};
    SymbolEntryPointer symbol_insertion_status;

    const char *mykeyword[4] = {"void","double","char","long"};
    const size_t keyword_length[4] = {4,6,4,4};
    const uint8_t sub_token[4] = {VOID, DOUBLE, CHAR, LONG};

    size_t i;
    size_t offset_pointer;

    allocation_status = allocate_string_pool(&string_pool_test, 8);
    allocation_status = allocate_symbol_pool(&symbol_pool_test, &string_pool_test , 2);

    if (allocation_status != NO_ERROR) {
        status_print(allocation_status);
        test_status.status = TEST_FAILED_RUNTIME_ERROR;
        test_status.message = "Runtime error\n";
    }

    test_token.sub_token_type = INT;
    symbol_insertion_status = insert_symbol(&symbol_pool_test, "int", 3, test_token);

    if (symbol_insertion_status.status != NO_ERROR) {
        status_print(symbol_insertion_status.status);
        test_status.status = TEST_FAILED_RUNTIME_ERROR;
        test_status.message = "Runtime error\n";
    }

    created_entry = symbol_pool_test.entries[symbol_insertion_status.symbol_id];

    if (created_entry.string_index != 0 || created_entry.string_length != 3) {
        test_status.status = TEST_FAILED_EXPECT_MISMATCH;
        test_status.message = "String pointer and length expected mismatch\n";
        return test_status;
    }

    if (memcmp(&created_entry.semantic, &test_token, sizeof(test_token))) {
        test_status.status = TEST_FAILED_EXPECT_MISMATCH;
        test_status.message = "Semantic token expected mismatch\n";
        return test_status;
    }

    test_token.sub_token_type = FLOAT;
    symbol_insertion_status = insert_symbol(&symbol_pool_test, "float", 5, test_token);

    if (symbol_insertion_status.status != NO_ERROR) {
        status_print(symbol_insertion_status.status);
        test_status.status = TEST_FAILED_RUNTIME_ERROR;
        test_status.message = "Runtime error\n";
    }

    created_entry = symbol_pool_test.entries[symbol_insertion_status.symbol_id];


    if (created_entry.string_index != 4 || created_entry.string_length != 5) {
        test_status.status = TEST_FAILED_EXPECT_MISMATCH;
        test_status.message = "String pointer and length expected mismatch\n";
        return test_status;
    }

    if (memcmp(&created_entry.semantic, &test_token, sizeof(test_token))) {
        test_status.status = TEST_FAILED_EXPECT_MISMATCH;
        test_status.message = "Semantic token expected mismatch\n";
        return test_status;
    }

    if (string_pool_test.capacity != 16){
        test_status.status = TEST_FAILED_EXPECT_MISMATCH;
        test_status.message = "Reallocation size isnt the same as expected";
        return test_status;
    }

    offset_pointer = 10;

    for (i = 0; i < 4; i++) {

        test_token.sub_token_type=sub_token[i];
        symbol_insertion_status = insert_symbol(&symbol_pool_test, mykeyword[i], keyword_length[i], test_token);

        if (symbol_insertion_status.status != NO_ERROR) {
            status_print(symbol_insertion_status.status);
            test_status.status = TEST_FAILED_RUNTIME_ERROR;
            test_status.message = "Runtime error\n";
        }

        created_entry = symbol_pool_test.entries[symbol_insertion_status.symbol_id];
        if (created_entry.string_index != offset_pointer || created_entry.string_length != keyword_length[i]) {
            test_status.status = TEST_FAILED_EXPECT_MISMATCH;
            test_status.message = "String pointer and length expected mismatch\n";
            return test_status;
        }

        if (memcmp(&created_entry.semantic, &test_token, sizeof(test_token))) {
            test_status.status = TEST_FAILED_EXPECT_MISMATCH;
            test_status.message = "Semantic token expected mismatch\n";
            return test_status;
        }
        offset_pointer += ( keyword_length[i] + 1 );
    }

    free_symbol_pool(&symbol_pool_test);

    if (symbol_pool_test.entries !=  NULL || symbol_pool_test.capacity != 0 || symbol_pool_test.count != 0) {
        test_status.status = TEST_FAILED_EXPECT_MISMATCH;
        test_status.message = "Symbol pool not freed correctly";
        return test_status;
    }

    if (symbol_pool_test.string_pool != NULL || string_pool_test.start_pointer !=  NULL || string_pool_test.capacity != 0 || string_pool_test.used != 0) {
        test_status.status = TEST_FAILED_EXPECT_MISMATCH;
        test_status.message = "String pool inside symbol pool not freed correctly";
        return test_status;
    }

    return test_status;
}
