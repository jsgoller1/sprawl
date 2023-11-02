include makefiles/settings_misc.mk
include makefiles/settings_compilation.mk

BERZERK_DIR:=sample_games/berzerk
BERZERK_ASSETS_DIR_PATH:=/Users/joshua/Code/sprawl/
BERZERK_MODULES:=3rdparty $(BERZERK_DIR) $(BERZERK_DIR)/animation $(BERZERK_DIR)/audio $(BERZERK_DIR)/drawing  $(BERZERK_DIR)/gameobject
BERZERK_MODULES:=$(BERZERK_MODULES) $(BERZERK_DIR)/gameobject/gameobject $(BERZERK_DIR)/gameobject/bullet $(BERZERK_DIR)/gameobject/robot
BERZERK_MODULES:=$(BERZERK_MODULES) $(BERZERK_DIR)/gameobject/wall $(BERZERK_DIR)/level $(BERZERK_DIR)/math $(BERZERK_DIR)/texture 
BERZERK_INCLUDES:=$(patsubst %, -I %,$(BERZERK_MODULES))
BERZERK_CXXFLAGS:=$(CXXFLAGS) $(BERZERK_INCLUDES)
BERZERK_SRC_FILES:=$(shell find $(BERZERK_MODULES) -name "*.cc" | sort -u)
BERZERK_OBJ_FILES:=$(patsubst %.cc, %.o, $(BERZERK_SRC_FILES))
BERZERK_SHARED_OBJ_FILES:=$(shell find 3rdparty/ -name "*.dylib" -or -name "*.so")
BERZERK_DEP_FILES := $(BERZERK_SRC_FILES:.cc=.d)
-include $(BERZERK_DEP_FILES)

deps: $(BERZERK_DEP_FILES)

%.d: %.cc
	$(CCACHE) $(CXX) $(BERZERK_CXXFLAGS) -MM $^>> $@;

%.o: %.cc
	$(CCACHE) $(CXX) $(BERZERK_CXXFLAGS) -c -o $@ $<

all: berserk 

build: $(BERZERK_OBJ_FILES)
	$(CCACHE) $(CXX) $(BERZERK_CXXFLAGS) $(BERZERK_OBJ_FILES) $(BERZERK_SHARED_OBJ_FILES) -o ./bin/berzerk

run:
	./bin/berzerk $(BERZERK_ASSETS_DIR_PATH)

count-loc:
	git ls-files | grep berzerk | grep -E "(\.cc|\.hh)$$" | uniq | xargs cat | wc -l

