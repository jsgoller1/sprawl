# Adapted from https://stackoverflow.com/a/28663974/1320882, and
# "Recursive Make Considered Harmful" by Peter Miller

include makefiles/ops.mk
include makefiles/settings.mk

SPRAWL_MODULES:=sprawl sprawl/cli sprawl/collision sprawl/components sprawl/drawing sprawl/ecs \
sprawl/input sprawl/input/event sprawl/logging sprawl/math sprawl/physics sprawl/wads 3rdparty
SPRAWL_INCLUDES:=$(patsubst %, -I %,$(SPRAWL_MODULES))
SPRAWL_CXXFLAGS:=$(CXXFLAGS) $(SPRAWL_INCLUDES)
SPRAWL_SRC_FILES:=$(shell find $(SPRAWL_MODULES) -name "*.cc" | sort -u)
SPRAWL_OBJ_FILES:=$(patsubst %.cc, %.o, $(SPRAWL_SRC_FILES))
SPRAWL_SHARED_OBJ_FILES:=$(shell find 3rdparty/ -name "*.dylib" -or -name "*.so")
sprawl: $(SPRAWL_OBJ_FILES)
	$(CCACHE) $(CXX) $(SPRAWL_CXXFLAGS) $(SPRAWL_OBJ_FILES) $(SPRAWL_SHARED_OBJ_FILES) -o $(ENGINE_BIN)

BERZERK_MODULES:=sample_games/berzerk 3rdparty
BERZERK_INCLUDES:=$(patsubst %, -I %,$(BERZERK_MODULES))
BERZERK_CXXFLAGS:=$(CXXFLAGS) $(BERZERK_INCLUDES)
BERZERK_SRC_FILES:=$(shell find $(BERZERK_MODULES) -name "*.cc" | sort -u)
BERZERK_OBJ_FILES:=$(patsubst %.cc, %.o, $(BERZERK_SRC_FILES))
BERZERK_SHARED_OBJ_FILES:=$(shell find 3rdparty/ -name "*.dylib" -or -name "*.so")
BERZERK_LEVEL_SPRITES:=/home/joshua/Code/sprawl/sample_games/berzerk/textures/level-sprites.png
BERZERK_CHARACTER_SPRITES:=/home/joshua/Code/sprawl/sample_games/berzerk/textures/character-sprites.png
BERZERK_TEXT_SPRITES:=/home/joshua/Code/sprawl/sample_games/berzerk/textures/text-sprites.png
berzerk: $(BERZERK_OBJ_FILES)
	$(CCACHE) $(CXX) $(BERZERK_CXXFLAGS) $(BERZERK_OBJ_FILES) $(BERZERK_SHARED_OBJ_FILES) -o ./bin/$@
	./bin/berzerk $(BERZERK_LEVEL_SPRITES) $(BERZERK_CHARACTER_SPRITES) $(BERZERK_TEXT_SPRITES)

BREAKOUT_MODULES:=sample_games/breakout 3rdparty
BREAKOUT_INCLUDES:=$(patsubst %, -I %,$(BREAKOUT_MODULES))
BREAKOUT_CXXFLAGS:=$(CXXFLAGS) $(BREAKOUT_INCLUDES)
BREAKOUT_SRC_FILES:=$(shell find $(BREAKOUT_MODULES) -name "*.cc" | sort -u)
BREAKOUT_OBJ_FILES:=$(patsubst %.cc, %.o, $(BREAKOUT_SRC_FILES))
BREAKOUT_SHARED_OBJ_FILES:=$(shell find 3rdparty/ -name "*.dylib" -or -name "*.so")
breakout: $(BREAKOUT_OBJ_FILES)
	$(CCACHE) $(CXX) $(BREAKOUT_CXXFLAGS) $(BREAKOUT_OBJ_FILES) $(BREAKOUT_SHARED_OBJ_FILES) -o ./bin/$@
	./bin/breakout



# Utilizes Clang preprocessor to automatically generate dependency 
# makefile targets; this target be evaluated every time the Makefile
# is read, so dependencies will be recalculated regularly. Inclusion
# will cause to make to restart with the new targets available
.depend: $(BERZERK_SRC_FILES) # $(BREAKOUT_SRC_FILES) $(SPRAWL_SRC_FILES)
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
	-find $(BREAKOUT_MODULES) -name "*.o" | sort -u | xargs rm
	-find $(BERZERK_MODULES) -name "*.o" | sort -u | xargs rm
	-find $(SPRAWL_MODULES) -name "*.o" | sort -u | xargs rm
