SRCS := main.c \
        utils/flat_array_hashmap.c \
        utils/string_arena_allocator.c \
        utils/file_loader.c \
        utils/parser.c \
        utils/lexer.c \
        utils/xxhash.c

TEST_SRCS := unit_test/main.c \
             unit_test/string_pool_test.c \
             unit_test/symbol_pool_test.c \
             unit_test/tokens_hashmap_test.c \
             unit_test/runtime_exec.c \
             unit_test/test.c \
             utils/tokens_hashmap.c \
             utils/string_pool.c \
             utils/symbol_pool.c \
             utils/file_loader.c \
             utils/char_manip.c \
             utils/new_parser.c \
             utils/new_lexer.c \
             utils/fnv1a32.c \
             utils/status.c


HEADERS := $(wildcard include/*.h)
TEST_HEADERS := $(wildcard include/*.h) $(wildcard unit_test/*.h)
INC_FLAGS := -Iinclude

.PHONY: all release debug

all: release debug

release: $(SRCS) $(HEADERS)
	gcc -O2 -march=native $(INC_FLAGS) $(SRCS) -o ./output/main

legacy: $(TEST_SRCS) $(TEST_HEADERS)
	gcc -O0 -std=c89 -pedantic-errors $(INC_FLAGS) $(TEST_SRCS)  -o ./output/main_legacy

test: $(TEST_SRCS) $(TEST_HEADERS)
	gcc -O0 -std=c89 -pedantic-errors $(INC_FLAGS) -g $(TEST_SRCS) -o ./output/main_test
