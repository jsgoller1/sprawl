include makefiles/settings_misc.mk
include makefiles/settings_compilation.mk

# TODO: Remove sample_games/mvp here and use separate makefile
SPRAWL_MODULES:=3rdparty sample_games/mvp $(shell find sprawl -type d)
SPRAWL_INCLUDES:=$(patsubst %, -I %,$(SPRAWL_MODULES)) -I/usr/local/include/SDL3_image -I/usr/local/include/SDL3
SPRAWL_COMPILE_CXXFLAGS:=$(CXXFLAGS) -fPIC -c $(SPRAWL_INCLUDES)
SPRAWL_LINK_CXXFLAGS:=$(CXXFLAGS) $(SPRAWL_INCLUDES)
SPRAWL_SRC_FILES:=$(shell find $(SPRAWL_MODULES) -name "*.cc" | sort -u)
SPRAWL_OBJ_FILES:=$(patsubst %.cc, %.o, $(SPRAWL_SRC_FILES))
SPRAWL_SHARED_OBJ_FILES:=$(shell find 3rdparty/ -name "*.dylib" -or -name "*.so")
SPRAWL_DEP_FILES := $(SPRAWL_SRC_FILES:.cc=.d)
-include $(SPRAWL_DEP_FILES)

deps: $(SPRAWL_DEP_FILES)

%.d: %.cc
	$(CCACHE) $(CXX) $(SPRAWL_COMPILE_CXXFLAGS) -MMD -MP -MF $@ -E $< > /dev/null

%.o: %.cc
	$(CCACHE) $(CXX) $(SPRAWL_COMPILE_CXXFLAGS) -c -o $@ $<

# TODO: Change this to not link into a final executable; this should be done by the game itself and named appropriately
build: $(SPRAWL_OBJ_FILES)
	$(CCACHE) $(CXX) $(SPRAWL_LINK_CXXFLAGS) $(SPRAWL_OBJ_FILES) $(SPRAWL_SHARED_OBJ_FILES) -lSDL3 -lSDL3_image -o $(ENGINE_BIN).lib




