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
INCLUDE := -I src/include -I src/managers/include -I src/components/include -I src/wads/include -I src/3rdparty/include
TEST_INCLUDE := $(INCLUDE) -I src/test/include
LINK := -lSDL2 -lSDL2_image
TEST_LINK := $(LINK) -lgtest_main -lgtest -lgmock 
CLANG_LINKER_ARGS := -Wl,-rpath -Wl,/usr/local/lib/ # For libsdl2_image
SOURCE := src/*.cc src/components/*.cc src/managers/*.cc src/wads/*.cc
MAIN_SOURCE := $(SOURCE) src/main/*.cc
TEST_SOURCE := $(SOURCE) src/test/*.cc
OUTFILE := $(BIN_DIR)/neon-rain
OUTPUT := -o $(OUTFILE)
CC_COMPILE:=$(ANALYZER) $(CC_COMPILER) $(CC_FLAGS) $(WARNINGS) $(IGNORE) $(CLANG_LINKER_ARGS) $(OUTPUT)
MAIN_COMPILE := $(CC_COMPILE) $(INCLUDE) $(LINK) $(MAIN_SOURCE)
TEST_COMPILE := $(CC_COMPILE) $(TEST_INCLUDE) $(TEST_LINK) $(TEST_SOURCE)

SCREEN_RECORD := byzanz-record -d 3 --x=760 --y=200 --width=1920 --height=1080 bin/recorded_screen.gif

all: clean
	$(MAIN_COMPILE)
	$(VALGRIND) $(OUTFILE)

### Binary cleanup
clean:
	reset
	-rm -r $(BIN_DIR)/
	-mkdir $(BIN_DIR)

record:
	$(SCREEN_RECORD)

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
