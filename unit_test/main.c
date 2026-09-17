

#include "status.h"
#include "test.h"
int main() {
    print_test_status(test_string_pool());
    print_test_status(test_symbol_pool());
    print_test_status(test_tokens_hashmap());
    status_print(runtime_exec());
}
