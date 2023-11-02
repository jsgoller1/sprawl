
# 
# 
# 
# 
# breakout: $(BREAKOUT_OBJ_FILES)
# 	$(CCACHE) $(CXX) $(BREAKOUT_CXXFLAGS) $(BREAKOUT_OBJ_FILES) $(BREAKOUT_SHARED_OBJ_FILES) -o ./bin/$@
# 	./bin/breakout

include makefiles/settings_misc.mk
include makefiles/settings_compilation.mk

BREAKOUT_MODULES:=sample_games/breakout 3rdparty
BREAKOUT_INCLUDES:=$(patsubst %, -I %,$(BREAKOUT_MODULES))
BREAKOUT_CXXFLAGS:=$(CXXFLAGS) $(BREAKOUT_INCLUDES)
BREAKOUT_SRC_FILES:=$(shell find $(BREAKOUT_MODULES) -name "*.cc" | sort -u)
BREAKOUT_OBJ_FILES:=$(patsubst %.cc, %.o, $(BREAKOUT_SRC_FILES))
BREAKOUT_SHARED_OBJ_FILES:=$(shell find 3rdparty/ -name "*.dylib" -or -name "*.so")
BREAKOUT_DEP_FILES := $(BREAKOUT_SRC_FILES:.cc=.d)
-include $(BREAKOUT_DEP_FILES)

deps: $(BREAKOUT_DEP_FILES)

%.d: %.cc
	$(CCACHE) $(CXX) $(BREAKOUT_CXXFLAGS) -MM $^>> $@;

%.o: %.cc
	$(CCACHE) $(CXX) $(BREAKOUT_CXXFLAGS) -c -o $@ $<

all: breakout  

build: $(BREAKOUT_OBJ_FILES)
	$(CCACHE) $(CXX) $(BREAKOUT_CXXFLAGS) $(BREAKOUT_OBJ_FILES) $(BREAKOUT_SHARED_OBJ_FILES) -o ./bin/breakout

run:
	./bin/breakout

count-loc:
	git ls-files | grep breakout | grep -E "(\.cc|\.hh)$$" | uniq | xargs cat | wc -l
