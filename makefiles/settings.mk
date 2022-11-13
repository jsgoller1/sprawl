### General vars
SHELL:=/bin/bash
DIR:=$(shell pwd)
BIN_DIR:=$(DIR)/bin
PLATFORM:=$(shell uname)
PROJECT_NAME:=sprawl
ENGINE_BIN:=$(BIN_DIR)/$(PROJECT_NAME)

### Uncomment this to run Clang's static analyzer while building; this makes the build slower.
#ANALYZER:=scan-build --status-bugs

### Valgrind target for memory analysis
#VALGRIND := valgrind -q --leak-check=full --show-leak-kinds=all --track-origins=yes --error-exitcode=42

### Compiler settings for C++
CXX:=clang++
CC_FLAGS:=-std=c++20 -g
#CC_FLAGS_DIAGNOSTIC:=-save-stats -ftime-report --verbose
#LINK:=-lSDL2 -lSDL2_image

### Uncomment this to cause any failed assumptions to crash the engine; if commented out,
### they will instead be logged at LogLevel::ERROR.
#WRONG_ASSUMPTIONS_FATAL:=-DFWRONG_ASSUMPTIONS_FATAL=true

# TODO: Compiling this on my macbook, these flags don't work, but this is not a true cross-platform solution.
# NOTE: Screen params are no longer supported here; adjust screen height and width via the WAD file. 
ifeq ($(PLATFORM),Linux)
#CLANG_LINKER_ARGS:=-Wl,-rpath -Wl,/usr/local/lib/
endif

# Warning settings
WARNINGS:=-Weverything -Werror
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

# We need to use C headers from other projects, for now.
IGNORED_WARNINGS:=$(IGNORED_WARNINGS) -Wno-deprecated
CXXFLAGS:=$(CC_FLAGS) $(WARNINGS) $(IGNORED_WARNINGS)

#build:
#	time $(MAIN_COMPILE) > $(BIN_DIR)/build.log 2>&1
#	mkdir $(BIN_DIR)/stats
#	mv *.stats $(BIN_DIR)/stats
