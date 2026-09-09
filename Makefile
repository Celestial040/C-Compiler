SRCS := main.c utils/flat_array_hashmap.c utils/string_arena_allocator.c utils/file_loader.c utils/parser.c utils/lexer.c utils/xxhash.c
HEADERS := $(wildcard include/*.h)
INC_FLAGS := -Iinclude

.PHONY: all release debug

all: release debug

release: $(SRCS) $(HEADERS)
	gcc -O2 -march=native $(INC_FLAGS) $(SRCS) -o ./output/main

debug: $(SRCS) $(HEADERS)
	gcc $(INC_FLAGS) -g $(SRCS) -o ./output/main_debug

basic: $(SRCS) $(HEADERS)
	gcc -O0 -march=native $(INC_FLAGS) $(SRCS) -o ./output/main_half
