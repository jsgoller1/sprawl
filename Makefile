# Adapted from https://stackoverflow.com/a/28663974/1320882, and
# "Recursive Make Considered Harmful" by Peter Miller

####################################
## Directories and misc variables ##
#################################### 
SHELL:=/bin/bash
DIR:=$(shell pwd)
BIN_DIR:=$(DIR)/bin
PLATFORM:=$(shell uname)

#######################
## Compiler settings ##
#######################
CCACHE:=ccache

### Uncomment this to run Clang's static analyzer while building; this makes the build slower.
#ANALYZER:=scan-build --status-bugs

### Uncomment to run Valgrind on target for memory analysis
#VALGRIND := valgrind -q --leak-check=full --show-leak-kinds=all --track-origins=yes --error-exitcode=42

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
# Padding is irrelevant, we have memory to waste
# TODO: Doesn't seem like a problem presently, but doesn't padding solve cache fetch / alignment issues? Need
# to confirm this is actually irrelevant.
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
# We need to use C headers from other projects, for now.
CXXFLAGS:=$(CXXFLAGS) -Wno-deprecated
# We're only building on MacOS and Linux right now, so using *nix paths is fine
CXXFLAGS:=$(CXXFLAGS) -Wno-poison-system-directories
# I don't personally use C-style casting or double underscore identifiers but SDL does.
CXXFLAGS:=$(CXXFLAGS) -Wno-old-style-cast -Wno-reserved-identifier -Wno-reserved-macro-identifier

####################
## Engine targets ##
####################
ENGINE_NAME:=sprawl
ENGINE_BIN:=$(BIN_DIR)/$(PROJECT_NAME)
SPRAWL_DIR:=sprawl
SPRAWL_MODULES:=$(SPRAWL_DIR) $(SPRAWL_DIR)/cli $(SPRAWL_DIR)/collision $(SPRAWL_DIR)/components $(SPRAWL_DIR)/drawing \
$(SPRAWL_DIR)/ecs $(SPRAWL_DIR)/input $(SPRAWL_DIR)/input/event $(SPRAWL_DIR)/logging $(SPRAWL_DIR)/math $(SPRAWL_DIR)/physics \
$(SPRAWL_DIR)/wads 3rdparty
SPRAWL_SRC_FILES:=$(shell find $(SPRAWL_MODULES) -name "*.cc" | sort -u)
SPRAWL_INCLUDES:=$(patsubst %, -I %,$(SPRAWL_MODULES))
SPRAWL_OBJ_FILES:=$(patsubst %.cc, %.o, $(SPRAWL_SRC_FILES))
SPRAWL_SHARED_OBJ_FILES:=$(shell find 3rdparty/ -name "*.dylib" -or -name "*.so")
SPRAWL_CXXFLAGS:=$(CXXFLAGS) $(SPRAWL_INCLUDES)

sprawl: $(SPRAWL_OBJ_FILES)
	$(CCACHE) $(CXX) $(SPRAWL_CXXFLAGS) $(SPRAWL_OBJ_FILES) $(SPRAWL_SHARED_OBJ_FILES) -o $(ENGINE_BIN)

##############################
## Integration test targets ##
##############################

include test/integration/integration.mk
MODULES:=test/integration  

SPRAWL_OBJ_FILES:=$(patsubst %.cc, %.o, $(SRC_FILES))
SPRAWL_SHARED_OBJ_FILES:=$(shell find 3rdparty/ -name "*.dylib" -or -name "*.so")

integration-test: sprawl 

# Utilizes Clang preprocessor to automatically generate dependency 
# makefile targets; this target be evaluated every time the Makefile
# is read, so dependencies will be recalculated regularly. Inclusion
# will cause to make to restart with the new targets available
.depend: $(SRC_FILES)
	rm -f ./$@
	$(CXX) $(CXXFLAGS) -MM $^>>./$@;
include .depend

clean-obj:
	-rm -f $(SPRAWL_OBJ_FILES)

clean-deps:
	-rm .depend

clean-logs:
	-rm bin/*.log

clean-bin:
	-rm $(ENGINE_BIN)

clean-purge: clean-deps clean-logs clean-bin
	find $(MODULES) -name "*.o" | sort -u | xargs rm

all: 
	@echo "No 'all' target; try 'make sprawl' or 'make mvp'"

# Ops-related makefiles; these involve automation
# and no compilation. 

