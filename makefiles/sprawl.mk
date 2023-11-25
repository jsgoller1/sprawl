include makefiles/settings_misc.mk
include makefiles/settings_compilation.mk

SPRAWL_MODULES:=sprawl sprawl/cli sprawl/collision sprawl/components sprawl/drawing sprawl/ecs 
SPRAWL_MODULES:=$(SPRAWL_MODULES) sprawl/input sprawl/input/event sprawl/logging sprawl/math sprawl/physics sprawl/wads 3rdparty
SPRAWL_INCLUDES:=$(patsubst %, -I %,$(SPRAWL_MODULES))
SPRAWL_COMPILE_CXXFLAGS:=$(CXXFLAGS) -fPIC -c $(SPRAWL_INCLUDES)
SPRAWL_LINK_CXXFLAGS:=$(CXXFLAGS) $(SPRAWL_INCLUDES)
SPRAWL_SRC_FILES:=$(shell find $(SPRAWL_MODULES) -name "*.cc" | sort -u)
SPRAWL_OBJ_FILES:=$(patsubst %.cc, %.o, $(SPRAWL_SRC_FILES))
SPRAWL_SHARED_OBJ_FILES:=$(shell find 3rdparty/ -name "*.dylib" -or -name "*.so")
SPRAWL_DEP_FILES := $(SPRAWL_SRC_FILES:.cc=.d)
-include $(SPRAWL_DEP_FILES)

deps: $(SPRAWL_DEP_FILES)

%.d: %.cc
	$(CCACHE) $(CXX) $(SPRAWL_COMPILE_CXXFLAGS) -MM $^>> $@;

%.o: %.cc
	$(CCACHE) $(CXX) $(SPRAWL_COMPILE_CXXFLAGS) -c -o $@ $<

build: $(SPRAWL_OBJ_FILES)
	$(CCACHE) $(CXX) $(SPRAWL_LINK_CXXFLAGS) $(SPRAWL_OBJ_FILES) $(SPRAWL_SHARED_OBJ_FILES) -o $(ENGINE_BIN).lib

count-loc:
	git ls-files | grep sprawl | grep -E "(\.cc|\.hh)$$" | uniq | xargs cat | wc -l


