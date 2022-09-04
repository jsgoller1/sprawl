### General vars
SHELL :=/bin/bash
BIN_DIR := $(shell pwd)/bin

### Uncomment this to run Clang's static analyzer while building; this makes the build slower.
ANALYZER:=scan-build --status-bugs

### Compiler settings for C++
CC_COMPILER:=clang++
CC_FLAGS :=-std=c++17 -g
#WARNINGS :=-Weverything -Werror
IGNORE := -Wno-c++98-compat
INCLUDE := -lSDL2 
CC_COMPILE:=$(ANALYZER) $(CC_COMPILER) $(CC_FLAGS) $(WARNINGS) $(IGNORE) $(INCLUDE)
OUTFILE := $(BIN_DIR)/neon-rain
OUTPUT := -o $(OUTFILE)

### Valgrind target for memory analysis
VALGRIND := valgrind -q --leak-check=full --show-leak-kinds=all --track-origins=yes --error-exitcode=42

### Binary cleanup
clean:
	reset
	-rm -r $(BIN_DIR)/
	-mkdir $(BIN_DIR)

install:
	apt-get -qq install -y \
	clang \
	clang-tools \
	lldb \
	libsdl2-dev \
	valgrind

all: clean
	$(CC_COMPILE) main.cc $(OUTPUT)
	$(OUTFILE)

