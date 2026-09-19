SRCS := main.c \
             utils/tokens_hashmap.c \
             \
             utils/dynamic_array/string_dynamic_array.c \
             utils/dynamic_array/symbol_dynamic_array.c \
             utils/dynamic_array/variable_dynamic_array.c \
             \
             utils/dynamic_array/function_details_dynamic_array.c \
             utils/dynamic_array/function_params_dynamic_array.c \
             \
             utils/dynamic_array/struct_details_dynamic_array.c \
             utils/dynamic_array/struct_members_dynamic_array.c \
             \
             utils/dynamic_array/enum_details_dynamic_array.c \
             utils/dynamic_array/enum_members_dynamic_array.c \
             \
             utils/dynamic_array/union_details_dynamic_array.c \
             utils/dynamic_array/union_members_dynamic_array.c \
             \
             utils/file_loader.c \
             utils/char_manip.c \
             utils/parser.c \
             utils/lexer.c \
             utils/fnv1a32.c \
             utils/status.c


HEADERS := $(wildcard include/*.h include/*/*.h)
INC_FLAGS := -Iinclude

.PHONY: all release debug

all: release debug

release: $(SRCS) $(HEADERS)
	gcc -O2 -march=native -std=c89 -pedantic-errors $(INC_FLAGS) $(SRCS)  -o ./output/main

test: $(SRCS) $(HEADERS)
	gcc -O0 -march=native -std=c89 -pedantic-errors $(INC_FLAGS) $(SRCS)  -o ./output/main_test

clean:
	rm -rf build

loc_count:
	find . \( -name '*.c' -o -name '*.h' \) | xargs wc -l

binary_size_check:
	ls -l -h output/

gdb_test:
	gcc -O0 -march=native -std=c89 -pedantic-errors $(INC_FLAGS) $(SRCS)  -o ./output/main_test
	gdb output/main_test
