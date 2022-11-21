### General vars
SHELL:=/bin/bash
DIR:=$(shell pwd)
BIN_DIR:=$(DIR)/bin
PLATFORM:=$(shell uname)
PROJECT_NAME:=sprawl
ENGINE_BIN:=$(BIN_DIR)/$(PROJECT_NAME)

### Uncomment this to run Clang's static analyzer while building; this makes the build slower.
#ANALYZER:=scan-build --status-bugs

### Uncomment to run Valgrind on target for memory analysis
#VALGRIND := valgrind -q --leak-check=full --show-leak-kinds=all --track-origins=yes --error-exitcode=42

### Compiler settings for C++
CCACHE:=ccache
CXX:=clang++
CXXFLAGS:=-std=c++20 -g

# Uncomment this to add diagnostic flags to clang that provide information
# about build times.
#CXXFLAGS:=$(CXXFLAGS) -save-stats -ftime-report --verbose

### Uncomment this to cause any failed assumptions to crash the engine; if commented out,
### they will instead be logged at LogLevel::ERROR.
#CXXFLAGS:=$(CXXFLAGS) -DFWRONG_ASSUMPTIONS_FATAL=true

# Warning settings
CXXFLAGS:=$(CXXFLAGS) -Weverything -Werror
# Don't care about C++98 backwards compatibility.
CXXFLAGS:=$(CXXFLAGS) -Wno-c++98-compat -Wno-c++98-compat-pedantic
# Padding is irrelevant, we have memory to waste.
CXXFLAGS:=$(CXXFLAGS) -Wno-padded 
# Constructors with parameters shadowing attributes makes them concise
# Elsewhere, we use shadowing intentionally so we can chain constructors or make it clear what attribute
# a parameter will be assigned to. 
CXXFLAGS:=$(CXXFLAGS) -Wno-shadow-field-in-constructor -Wno-shadow-field -Wno-shadow
# We don't need to worry about missing values of an enum in a switch as long as we use a default path
CXXFLAGS:=$(CXXFLAGS) -Wno-switch-enum
# Loggers created at compile time are destroyed at exit time, but clang throws
# warnings and ignores [[clang::always_destroy]], so we're just going to disable the warning. 
CXXFLAGS:=$(CXXFLAGS) -Wno-global-constructors -Wno-exit-time-destructors
# We use va_args for format strings in logging, currently
CXXFLAGS:=$(CXXFLAGS) -Wno-format-nonliteral
# We need to use C headers from other projects, for now.
CXXFLAGS:=$(CXXFLAGS) -Wno-deprecated
