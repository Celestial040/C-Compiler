SRCS := main.c \
             utils/tokens_hashmap.c \
             utils/string_dynamic_array.c \
             utils/symbol_dynamic_array.c \
             utils/file_loader.c \
             utils/char_manip.c \
             utils/parser.c \
             utils/lexer.c \
             utils/fnv1a32.c \
             utils/status.c


HEADERS := $(wildcard include/*.h)
INC_FLAGS := -Iinclude

.PHONY: all release debug

all: release debug

release: $(SRCS) $(HEADERS)
	gcc -O2 -march=native -std=c89 -pedantic-errors $(INC_FLAGS) $(SRCS)  -o ./output/main

test: $(SRCS) $(HEADERS)
	gcc -O0 -march=native -std=c89 -pedantic-errors $(INC_FLAGS) $(SRCS)  -o ./output/main_test
