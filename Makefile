SRCS := main.c \
             utils/tokens_hashmap.c \
             \
             utils/vector/string.c \
             utils/vector/symbol.c \
             utils/vector/variable.c \
             \
             utils/vector/function_details.c \
             utils/vector/function_params.c \
             \
             utils/vector/struct_details.c \
             utils/vector/struct_members.c \
             \
             utils/vector/enum_details.c \
             utils/vector/enum_members.c \
             \
             utils/vector/union_details.c \
             utils/vector/union_members.c \
             \
             utils/file_loader.c \
             utils/char_manip.c \
             utils/parser.c \
             utils/lexer.c \
             utils/fnv1a32.c \
             utils/status.c

HEADERS := $(wildcard include/*.h include/*/*.h)
INC_FLAGS := -Iinclude
STRICT_CHECK_FLAG := -Wpedantic -Wall -Wextra -Wconversion -Wshadow -Wformat=2 -Wcast-qual -Wnull-dereference -Wstrict-prototypes -Wvla -Werror
CHECK_FLAG := -Wpedantic -Wall -Wextra -Werror

.PHONY: all release debug

all: release debug

release: $(SRCS) $(HEADERS)
	gcc -O2 -march=native -std=c89 -pedantic-errors $(INC_FLAGS) $(SRCS)  -o ./output/main

test: $(SRCS) $(HEADERS)
	gcc -O0 -march=native -std=c89 $(CHECK_FLAG) $(INC_FLAGS) $(SRCS)  -o ./output/main_test

strict_test: $(SRCS) $(HEADERS)
	gcc -O0 -march=native -std=c89 $(STRICT_CHECK_FLAG) $(INC_FLAGS) $(SRCS)  -o ./output/main_test

clean:
	rm -rf build

loc_count:
	find . \( -name '*.c' -o -name '*.h' \) | xargs wc -l

binary_size_check:
	ls -l -h output/



gdb_test:
	gcc -O0 -march=native -std=c89 -pedantic-errors $(INC_FLAGS) $(SRCS)  -o ./output/main_test
	gdb output/main_test
