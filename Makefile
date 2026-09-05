SRCS := main.c utils/hashmap.c utils/file_loader.c utils/parser.c utils/lexer.c
HEADERS := $(wildcard include/*.h)
INC_FLAGS := -Iinclude

.PHONY: all release debug

all: release debug

release: $(SRCS) $(HEADERS)
	gcc $(INC_FLAGS) $(SRCS) -o ./output/main

debug: $(SRCS) $(HEADERS)
	gcc $(INC_FLAGS) -g $(SRCS) -o ./output/main_debug
