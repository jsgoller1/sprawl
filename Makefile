# This is the top-level Makefile for the Sprawl project. Execute these targets from the root directory of the project. 
# See makefiles/README.md for more information.

.PHONY: sprawl sprawl-physics-test berzerk breakout 

MAKEFILE_DIR:=makefiles
include $(MAKEFILE_DIR)/settings_misc.mk

all: sprawl berzerk breakout mvp

# Builds main .dylib file for sprawl-based games to link against
sprawl:  
	$(MAKE) -j -f $(MAKEFILE_DIR)/sprawl.mk deps 
	$(MAKE) -j -f $(MAKEFILE_DIR)/sprawl.mk build 

# Runs sprawl MVP demonstrating basic functionality
mvp: sprawl 
	$(MAKE) -j -f $(MAKEFILE_DIR)/mvp.mk deps
	$(MAKE) -j -f $(MAKEFILE_DIR)/mvp.mk build

run-mvp:
	$(MAKE) -j -f $(MAKEFILE_DIR)/mvp.mk run


# Builds and runs breakout sample game
breakout:
	$(MAKE) -j -f $(MAKEFILE_DIR)/breakout.mk deps 
	$(MAKE) -j -f $(MAKEFILE_DIR)/breakout.mk build 

run-breakout:
	$(MAKE) -j -f $(MAKEFILE_DIR)/breakout.mk run  

# Builds and runs berzerk sample game
berzerk:
	$(MAKE) -j -f $(MAKEFILE_DIR)/berzerk.mk deps 
	$(MAKE) -j -f $(MAKEFILE_DIR)/berzerk.mk build 

run-berzerk:
	$(MAKE) -j -f $(MAKEFILE_DIR)/berzerk.mk run

clean-all: clean-bin clean-deps clean-logs clean-obj

clean-bin:
	-rm -r $(BIN_DIR)
	-mkdir $(BIN_DIR)

clean-deps:
	-find . -name "*.d" | sort -u | xargs rm

clean-logs:
	-rm -r $(LOG_DIR)
	-mkdir $(LOG_DIR)

clean-obj:
	-find . -name "*.o" | sort -u | xargs rm

# NOTE: This is a Linux-specific tool for screen recording. For MacOS, use Quicktime. 
record-screen:
	byzanz-record -d 5 --x=760 --y=200 --width=1920 --height=1080 bin/recorded_screen.gif

# NOTE: if you copy/paste this into the terminal, change the double-dollar sign to a single dollar sign.
count-sprawl-loc:
	git ls-files | grep sprawl | grep -E "(\.cc|\.hh)$$" | uniq | xargs cat | wc -l
