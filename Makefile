SRCS := main.c utils/flat_array_hashmap.c utils/string_arena_allocator.c utils/file_loader.c utils/parser.c utils/lexer.c utils/xxhash.c
TEST_SRCS := unit_test/main.c unit_test/string_pool_test.c unit_test/symbol_pool_test.c utils/tokens_hashmap.c utils/string_pool.c utils/symbol_pool.c utils/file_loader.c
HEADERS := $(wildcard include/*.h)
TEST_HEADERS := $(wildcard include/*.h) $(wildcard unit_test/*.h)
INC_FLAGS := -Iinclude

.PHONY: all release debug

all: release debug

release: $(SRCS) $(HEADERS)
	gcc -O2 -march=native $(INC_FLAGS) $(SRCS) -o ./output/main

legacy: $(SRCS) $(HEADERS)
	gcc -O0 -std=c89 $(INC_FLAGS) $(SRCS) -o ./output/main

fast: $(SRCS) $(HEADERS)
	gcc $(INC_FLAGS) -g $(SRCS) -o ./output/main_debug

test: $(TEST_SRCS) $(TEST_HEADERS)
	gcc $(INC_FLAGS) -g $(TEST_SRCS) -o ./output/main_test
