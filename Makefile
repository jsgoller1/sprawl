# Adapted from https://stackoverflow.com/a/28663974/1320882, and
# "Recursive Make Considered Harmful" by Peter Miller

include makefiles/settings.mk
include test/integration/integration.mk

MODULES:=sample_games/breakout 3rdparty
#MODULES:=$(MODULES) sprawl sprawl/cli sprawl/collision sprawl/components sprawl/drawing sprawl/ecs \
sprawl/input sprawl/input/event sprawl/logging sprawl/math sprawl/physics sprawl/wads 3rdparty
INCLUDES:=$(patsubst %, -I %,$(MODULES))
CXXFLAGS:=$(CXXFLAGS) $(INCLUDES)

SRC_FILES:=$(shell find $(MODULES) -name "*.cc" | sort -u)
OBJ_FILES:=$(patsubst %.cc, %.o, $(SRC_FILES))
SHARED_OBJ_FILES:=$(shell find 3rdparty/ -name "*.dylib" -or -name "*.so")

all: breakout

sprawl: $(OBJ_FILES)
	$(CCACHE) $(CXX) $(CXXFLAGS) $(OBJ_FILES) $(SHARED_OBJ_FILES) -o $(ENGINE_BIN)

breakout: $(OBJ_FILES)
	$(CCACHE) $(CXX) $(CXXFLAGS) $(OBJ_FILES) $(SHARED_OBJ_FILES) -o ./bin/breakout
	./bin/breakout


# Utilizes Clang preprocessor to automatically generate dependency 
# makefile targets; this target be evaluated every time the Makefile
# is read, so dependencies will be recalculated regularly. Inclusion
# will cause to make to restart with the new targets available
.depend: $(SRC_FILES)
	rm -f ./$@
	$(CXX) $(CXXFLAGS) -MM $^>>./$@;
include .depend

clean-obj:
	-rm -f $(OBJ_FILES)

clean-deps:
	-rm .depend

clean-logs:
	-rm bin/*.log

clean-bin:
	-rm $(ENGINE_BIN)

clean-purge: clean-deps clean-logs clean-bin
	find $(MODULES) -name "*.o" | sort -u | xargs rm

# Ops-related makefiles; these involve automation
# and no compilation. 
include makefiles/ops.mk
