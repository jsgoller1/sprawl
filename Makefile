include makefiles/settings.mk

MODULES:=3rdparty/fmt 3rdparty/json 3rdparty/sdl 3rdparty/sdl_image 
MODULES:=$(MODULES) sprawl/ sprawl/components/ sprawl/ecs sprawl/logging 
MODULES:=$(MODULES) sprawl/main sprawl/math sprawl/physics sprawl/wads 
INCLUDES:=$(patsubst %, -I %,$(MODULES))
CXXFLAGS:=$(CXXFLAGS) $(INCLUDES)

SRC_FILES:=$(shell find $(MODULES) -name "*.cc")
OBJ_FILES:=$(patsubst %.cc, %.o, $(SRC_FILES))
SHARED_OBJ_FILES:=$(shell find 3rdparty/ -name "*.so")

all: $(PROJECT_NAME)

$(PROJECT_NAME): $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) $(OBJ_FILES) $(SHARED_OBJ_FILES) -o ./bin/$(PROJECT_NAME)

depend: .depend

.depend: $(SRC_FILES)
	rm -f ./.depend
	$(CXX) $(CXXFLAGS) -MM $^>>./.depend;

clean:
	rm -f $(OBJ_FILES)

dist-clean: clean
	rm -f *~ .depend

include .depend

# Ops-related makefiles; these involve automation
# and no compilation. 
include makefiles/ops.mk
include makefiles/playtests.mk
