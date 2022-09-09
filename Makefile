### General vars
SHELL :=/bin/bash
BIN_DIR := $(shell pwd)/bin

### Uncomment this to run Clang's static analyzer while building; this makes the build slower.
#ANALYZER:=scan-build --status-bugs

### Valgrind target for memory analysis
#VALGRIND := valgrind -q --leak-check=full --show-leak-kinds=all --track-origins=yes --error-exitcode=42

### Compiler settings for C++
CC_COMPILER:=clang++ 
CC_FLAGS :=-std=c++17 -g
#WARNINGS :=-Weverything -Werror
IGNORE := -Wno-c++98-compat
LIBDIR := -Wl,-rpath -Wl,/usr/local/lib/ # For libsdl2_image
INCLUDE := -I src/include
LINK := -lSDL2 -lSDL2_image
CC_COMPILE:=$(ANALYZER) $(CC_COMPILER) $(CC_FLAGS) $(WARNINGS) $(IGNORE) $(INCLUDE) $(LINK) $(LIBDIR)
OUTFILE := $(BIN_DIR)/neon-rain
OUTPUT := -o $(OUTFILE)

all: clean
	$(CC_COMPILE) src/*.cc $(OUTPUT)
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

