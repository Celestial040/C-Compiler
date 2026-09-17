#include "status.h"
#include "symbol_pool.h"
#include "test.h"
#include "tokens_hashmap.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

TestStatusStruct test_tokens_hashmap() {

    TestStatusStruct test_status = {.status=TEST_SUCCESS, .message="Tokens Hashmap Test Success \n"};

    StringPool string_pool_test;
    Status allocation_status = allocate_string_pool(&string_pool_test, 10);
    if (allocation_status != NO_ERROR) {
        status_print(allocation_status);
        test_status.status = TEST_FAILED_RUNTIME_ERROR;
        test_status.message = "Runtime error\n";
    }

    SymbolPool symbol_pool_test;
    allocation_status = allocate_symbol_pool(&symbol_pool_test, &string_pool_test , 4);

    if (allocation_status != NO_ERROR) {
        status_print(allocation_status);
        test_status.status = TEST_FAILED_RUNTIME_ERROR;
        test_status.message = "Runtime error\n";
    }

    TokensHashMap tokens_hashmap_test;
    allocation_status = allocate_hashmap(&tokens_hashmap_test,&symbol_pool_test, 4);
    if (allocation_status != NO_ERROR) {
        status_print(allocation_status);
        test_status.status = TEST_FAILED_RUNTIME_ERROR;
        test_status.message = "Runtime error\n";
    }

    Semantic test_token1 = {.symbol_type=SYMBOL_KEYWORD , .token_type=TOKEN_KEYWORD, .sub_token_type=INT};
    SymbolEntryPointer symbol_insertion_status = insert_symbol(&symbol_pool_test, "int", 3, test_token1);

    if (symbol_insertion_status.status != NO_ERROR) {
        status_print(symbol_insertion_status.status);
        test_status.status = TEST_FAILED_RUNTIME_ERROR;
        test_status.message = "Runtime error\n";
    }

    Status insertion_status = insert_item(&tokens_hashmap_test, "int", 3, symbol_insertion_status.symbol_id);

    if (allocation_status != NO_ERROR) {
        status_print(allocation_status);
        test_status.status = TEST_FAILED_RUNTIME_ERROR;
        test_status.message = "Runtime error\n";
    }

    TokenStatus search_result = lookup_item(&tokens_hashmap_test, "int", 3,2);

    if (search_result.status != NO_ERROR) {
        status_print(search_result.status);
        test_status.status = TEST_FAILED_RUNTIME_ERROR;
        test_status.message = "Runtime error\n";
    }

    Token result_token = search_result.token;

    if (result_token.line != 2 || result_token.symbol_id !=  symbol_insertion_status.symbol_id) {
        test_status.status = TEST_FAILED_EXPECT_MISMATCH;
        test_status.message = "Semantic token expected mismatch\n";
        return test_status;
    }

    if (result_token.token_type != TOKEN_KEYWORD || result_token.sub_token_type != INT ) {
        test_status.status = TEST_FAILED_EXPECT_MISMATCH;
        test_status.message = "Semantic token expected mismatch\n";
        return test_status;
    }

    const char *mykeyword[4] = {"float","double","char","long"};
    const size_t keyword_length[4] = {5,6,4,4};
    const uint8_t sub_token[4] = {FLOAT, DOUBLE, CHAR, LONG};

    for (size_t i = 0; i < 4; i++) {
        Semantic test_token = {.symbol_type=SYMBOL_KEYWORD , .token_type=TOKEN_KEYWORD, .sub_token_type=sub_token[i]};
        SymbolEntryPointer symbol_insertion_status = insert_symbol(&symbol_pool_test, mykeyword[i], keyword_length[i], test_token);
        Status insertion_status = insert_item(&tokens_hashmap_test, mykeyword[i], keyword_length[i], symbol_insertion_status.symbol_id);

        TokenStatus search_result = lookup_item(&tokens_hashmap_test, mykeyword[i], keyword_length[i],2+i*2);

        if (search_result.status != NO_ERROR) {
            status_print(search_result.status);
            test_status.status = TEST_FAILED_RUNTIME_ERROR;
            test_status.message = "Runtime error\n";
        }

        Token result_token = search_result.token;

        if (result_token.line != 2+i*2 || result_token.symbol_id !=  symbol_insertion_status.symbol_id) {
            test_status.status = TEST_FAILED_EXPECT_MISMATCH;
            test_status.message = "Semantic token expected mismatch\n";
            return test_status;
        }

        if (result_token.token_type != TOKEN_KEYWORD || result_token.sub_token_type != sub_token[i] ) {
            test_status.status = TEST_FAILED_EXPECT_MISMATCH;
            test_status.message = "Semantic token expected mismatch\n";
            return test_status;
        }
    }

    return test_status;
}
