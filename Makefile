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
WARNINGS := -Weverything -Werror
IGNORE := -Wno-c++98-compat
INCLUDE := -I src/include -I src/3rdparty/include -I src/components/include -I src/managers/include -I src/physics/include  -I src/wads/include 
LINK := -lSDL2 -lSDL2_image
CLANG_LINKER_ARGS := -Wl,-rpath -Wl,/usr/local/lib/ # For libsdl2_image
SOURCE := src/*.cc src/components/*.cc src/managers/*.cc src/wads/*.cc
CC_COMPILE:=$(ANALYZER) $(CC_COMPILER) $(CC_FLAGS) $(WARNINGS) $(IGNORE) $(CLANG_LINKER_ARGS) 

MAIN_SOURCE := $(SOURCE) src/main/*.cc
MAIN_OUTPUT := -o $(BIN_DIR)/neon-rain
MAIN_COMPILE := $(CC_COMPILE) $(MAIN_OUTPUT) $(INCLUDE) $(LINK) $(MAIN_SOURCE)

TEST_INCLUDE := $(INCLUDE) -I src/test/include
TEST_LINK := $(LINK) -lgtest_main -lgtest -lgmock 
TEST_SOURCE := $(SOURCE) src/test/*.cc
TEST_OUTPUT := -o $(BIN_DIR)/neon-rain
TEST_COMPILE := $(CC_COMPILE) $(TEST_OUTPUT) $(TEST_INCLUDE) $(TEST_LINK) $(TEST_SOURCE)

all: clean
	$(MAIN_COMPILE)
	$(VALGRIND) $(OUTFILE)

### Binary cleanup
clean:
	reset
	-rm -r $(BIN_DIR)/
	-mkdir $(BIN_DIR)

record:
	byzanz-record -d 3 --x=760 --y=200 --width=1920 --height=1080 bin/recorded_screen.gif

install-devtools:
	apt-get -qq install -y \
	byzanz-record \ 
	clang \
	clang-tools \
	lldb \
	libsdl2-dev \
	valgrind

test: 
	$(TEST_COMPILE)
	$(VALGRIND) $(OUTFILE)
