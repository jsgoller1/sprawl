### General vars
SHELL:=/bin/bash
DIR:=$(shell pwd)
BIN_DIR:=$(DIR)/bin
PLATFORM:=$(shell uname)

### Uncomment this to run Clang's static analyzer while building; this makes the build slower.
#ANALYZER:=scan-build --status-bugs

### Valgrind target for memory analysis
#VALGRIND := valgrind -q --leak-check=full --show-leak-kinds=all --track-origins=yes --error-exitcode=42

### Compiler settings for C++
CC_COMPILER:=clang++
CC_FLAGS:=-std=c++20 -g
INCLUDE:=-I src/include -I src/3rdparty/fmt/include -I src/3rdparty/json/include -I src/components/include -I src/ecs/include -I src/logging/include -I src/math/include -I src/physics/include -I src/wads/include 
LINK:=-lSDL2 -lSDL2_image
SOURCE:=src/*.cc src/3rdparty/fmt/*.cc src/components/*.cc src/ecs/*.cc src/logging/*.cc src/math/*.cc src/physics/*.cc src/wads/*.cc

### Uncomment this to cause any failed assumptions to crash the engine; if commented out,
### they will instead be logged at LogLevel::ERROR.
#WRONG_ASSUMPTIONS_FATAL:=-DFWRONG_ASSUMPTIONS_FATAL=true

# TODO: Compiling this on my macbook, these flags don't work, but this is not a true cross-platform solution.
# NOTE: Screen params are no longer supported here; adjust screen height and width via the WAD file. 
ifeq ($(PLATFORM),Linux)
#SCREEN_PARAMS:=-DSCREEN_HEIGHT=1080 -DSCREEN_WIDTH=1920
# For libsdl2_image
CLANG_LINKER_ARGS:=-Wl,-rpath -Wl,/usr/local/lib/
WARNINGS:=-Weverything -Werror
endif
ifeq ($(PLATFORM),Darwin)
#SCREEN_PARAMS:=-DSCREEN_WIDTH=1440 -DSCREEN_HEIGHT=900
endif

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
# Loggers created at compile time are destroyed at exit time, but clang throws
# warnings and ignores [[clang::always_destroy]], so we're just going to disable the warning. 
IGNORED_WARNINGS:=$(IGNORED_WARNINGS) -Wno-global-constructors -Wno-exit-time-destructors
# We use va_args for format strings in logging, currently
IGNORED_WARNINGS:=$(IGNORED_WARNINGS) -Wno-format-nonliteral
# Virtual methods without a virtual destructor can lead to a situation where an overriden method in a derived
# class uses something that needs special cleanup but can't do the cleanup in the destructor since it can't be overridden. 
# We don't have that problem right now, and generally won't since we do all cleanup via smart pointers.
#IGNORED_WARNINGS:=$(IGNORED_WARNINGS) -Wno-non-virtual-dtor


CC_COMPILE:=$(ANALYZER) $(CC_COMPILER) $(CC_FLAGS) $(FATAL_ASSERTIONS) $(WARNINGS) $(IGNORED_WARNINGS) $(CLANG_LINKER_ARGS)

MAIN_SOURCE:=$(SOURCE) src/main/*.cc
MAIN_INCLUDE:=$(INCLUDE) -I src/main/include
MAIN_OUTFILE:=$(BIN_DIR)/sprawl
MAIN_OUTPUT:=-o $(MAIN_OUTFILE)
MAIN_COMPILE:=$(CC_COMPILE) $(MAIN_INCLUDE) $(LINK) $(MAIN_SOURCE) $(MAIN_OUTPUT) 
MAIN_LOGFILE:=$(BIN_DIR)/sprawl-logfile-`date --rfc-3339=ns | awk '{print $$2}'`.log

TEST_INCLUDE:=$(INCLUDE) -I src/test/include
TEST_LINK:=$(LINK) -lgtest_main -lgtest -lgmock 
TEST_SOURCE:=$(SOURCE) src/test/*.cc
TEST_OUTFILE:=$(BIN_DIR)/sprawl-test
TEST_OUTPUT:=-o $(TEST_OUTFILE)
TEST_COMPILE:=$(CC_COMPILE) $(TEST_INCLUDE) $(TEST_LINK) $(TEST_SOURCE) $(TEST_OUTPUT) 

RECORD_CMD:=byzanz-record -d 5 --x=760 --y=200 --width=1920 --height=1080 bin/recorded_screen.gif

all: clean build mvp
	
build:
	time $(MAIN_COMPILE)

clean:
	reset
	-rm -r $(BIN_DIR)/
	-mkdir $(BIN_DIR)


install-devtools:
	apt-get -qq install -y \
	byzanz-record \ 
	clang \
	clang-tools \
	lldb \
	libsdl2-dev \
	valgrind

LOGGING_INCLUDES:=-I src/logging/include -I src/3rdparty/fmt/include  -I src/math/include -I src/include
LOGGING_SRC:=src/3rdparty/fmt/*.cc src/logging/*.cc src/logging/demo/*.cc src/math/*.cc
LOGGING_OUTFILE:=$(BIN_DIR)/loggingDemo
logging-demo:
	$(CC_COMPILE) $(LINK) $(LOGGING_INCLUDES) $(LOGGING_SRC) -o $(LOGGING_OUTFILE) 
	$(LOGGING_OUTFILE)

record:
	$(RECORD_CMD)

mvp: 
	$(MAIN_OUTFILE) $(DIR)/wads/playtests/mvp 


physics-test-collision-elastic:
	$(MAIN_OUTFILE) $(DIR)/wads/playtests/physics-tests/collision-elastic 2>&1 | tee $(MAIN_LOGFILE)

physics-test-collision-elastic-line-up:
	$(MAIN_OUTFILE) $(DIR)/wads/playtests/physics-tests/collision-elastic-line-up 2>&1 | tee $(MAIN_LOGFILE)

physics-test-collision-elastic-stack-up:
	$(MAIN_OUTFILE) $(DIR)/wads/playtests/physics-tests/collision-elastic-stack-up 2>&1 | tee $(MAIN_LOGFILE)

physics-test-collision-inelastic:
	$(MAIN_OUTFILE) $(DIR)/wads/playtests/physics-tests/collision-inelastic 2>&1 | tee $(MAIN_LOGFILE)

physics-test-collision-inelastic-edge-catch:
	$(MAIN_OUTFILE) $(DIR)/wads/playtests/physics-tests/collision-inelastic-edge-catch 2>&1 | tee $(MAIN_LOGFILE)

physics-test-gravity:
	$(MAIN_OUTFILE) $(DIR)/wads/playtests/physics-tests/gravity 2>&1 | tee $(MAIN_LOGFILE)

physics-tests: \
physics-test-collision-elastic \
physics-test-collision-elastic-line-up \
physics-test-collision-elastic-stack-up \
physics-test-collision-inelastic \
physics-test-collision-inelastic-edge-catch \
physics-test-gravity

rebuild: clean build

test: 
	$(TEST_COMPILE)
	$(VALGRIND) $(TEST_OUTFILE)


test-uname:
	echo $(PLATFORM) $(SOME_THING)


