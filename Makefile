### General vars
SHELL:=/bin/bash
BIN_DIR:=$(shell pwd)/bin

### Uncomment this to run Clang's static analyzer while building; this makes the build slower.
#ANALYZER:=scan-build --status-bugs

### Valgrind target for memory analysis
#VALGRIND := valgrind -q --leak-check=full --show-leak-kinds=all --track-origins=yes --error-exitcode=42

### Compiler settings for C++
CC_COMPILER:=clang++
CC_FLAGS:=-std=c++20 -g
WARNINGS:=-Weverything -Werror
INCLUDE:=-I src/include -I src/3rdparty/include -I src/collisions/include -I src/components/include
INCLUDE:=$(INCLUDE) -I src/ecs/include -I src/physics/include  -I src/wads/include 
LINK:=-lSDL2 -lSDL2_image
CLANG_LINKER_ARGS:=-Wl,-rpath -Wl,/usr/local/lib/ # For libsdl2_image
SOURCE:=src/*.cc src/collisions/*.cc src/components/*.cc src/ecs/*.cc src/physics/*.cc src/wads/*.cc
#### Warnings we ignore, with explanations
 # Don't care about C++98 backwards compatibility.
IGNORED_WARNINGS:=-Wno-c++98-compat -Wno-c++98-compat-pedantic  
# Padding is irrelevant, we have memory to waste.
IGNORED_WARNINGS:=$(IGNORED_WARNINGS) -Wno-padded 
# Constructors with parameters shadowing attributes makes them concise
# Elsewhere, we use shadowing intentionally so we can chain constructors or make it clear what attribute
# a parameter will be assigned to. 
IGNORED_WARNINGS:=$(IGNORED_WARNINGS) -Wno-shadow-field-in-constructor -Wno-shadow-field -Wno-shadow
# We don't need to worry about missing values of an enum in a switch as long as we use a default path
IGNORED_WARNINGS:=$(IGNORED_WARNINGS) -Wno-switch-enum
# nlohmann/json is a 3rd party library; no need to handle any warnings from it.
IGNORED_WARNINGS:=$(IGNORED_WARNINGS) -Wno-everything 

CC_COMPILE:=$(ANALYZER) $(CC_COMPILER) $(CC_FLAGS) $(WARNINGS) $(IGNORED_WARNINGS) $(CLANG_LINKER_ARGS) 

MAIN_SOURCE:=$(SOURCE) src/main/*.cc
MAIN_OUTFILE:=$(BIN_DIR)/neon-rain
MAIN_OUTPUT:=-o $(MAIN_OUTFILE)
MAIN_COMPILE:=$(CC_COMPILE) $(INCLUDE) $(LINK) $(MAIN_SOURCE) $(MAIN_OUTPUT) 
MAIN_LOGFILE:=sprawl-logfile-`date --rfc-3339=ns | awk '{print $$2}'`.log

TEST_INCLUDE:=$(INCLUDE) -I src/test/include
TEST_LINK:=$(LINK) -lgtest_main -lgtest -lgmock 
TEST_SOURCE:=$(SOURCE) src/test/*.cc
TEST_OUTFILE:=$(BIN_DIR)/neon-rain-test
TEST_OUTPUT:=-o $(TEST_OUTFILE)
TEST_COMPILE:=$(CC_COMPILE) $(TEST_INCLUDE) $(TEST_LINK) $(TEST_SOURCE) $(TEST_OUTPUT) 

all: clean build run
	
build:
	$(MAIN_COMPILE)

run: 
	$(VALGRIND) $(MAIN_OUTFILE) > $(MAIN_LOGFILE)

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
	$(VALGRIND) $(TEST_OUTFILE)
