### General vars
SHELL :=/bin/bash
BIN_DIR := $(shell pwd)/bin

### Uncomment this to run Clang's static analyzer while building; this makes the build slower.
#ANALYZER:=scan-build --status-bugs

### Valgrind target for memory analysis
#VALGRIND := valgrind -q --leak-check=full --show-leak-kinds=all --track-origins=yes --error-exitcode=42

### Compiler settings for C++
CC_COMPILER:=clang++
CC_FLAGS :=-std=c++20 -g
WARNINGS :=# -Weverything -Werror
IGNORE := -Wno-c++98-compat
INCLUDE := -I src/include -I src/managers/include -I src/components/include
LINK := -lSDL2 -lSDL2_image
CLANG_LINKER_ARGS := -Wl,-rpath -Wl,/usr/local/lib/ # For libsdl2_image
SOURCE := src/*.cc src/components/*.cc src/managers/*.cc
OUTFILE := $(BIN_DIR)/neon-rain
OUTPUT := -o $(OUTFILE)
CC_COMPILE:=$(ANALYZER) $(CC_COMPILER) $(CC_FLAGS) $(WARNINGS) $(IGNORE) $(INCLUDE) $(LINK) $(CLANG_LINKER_ARGS) $(SOURCE) $(OUTPUT)

all: clean
	$(CC_COMPILE)
	$(VALGRIND) $(OUTFILE)

### Binary cleanup
clean:
	reset
	-rm -r $(BIN_DIR)/
	-mkdir $(BIN_DIR)

install-devtools:
	apt-get -qq install -y \
	clang \
	clang-tools \
	lldb \
	libsdl2-dev \
	valgrind

