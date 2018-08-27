
# XXX tidy this up
LLVM_BEACONS_PATH := /home/rudy/beacons/llvm3.8
GTB_PATH          := llvm/lib/Transforms/beacons/beacon_lib


LDFLAGS := -L$(LLVM_BEACONS_PATH)/$(GTB_PATH)/gtb

all:
	gcc mat_mult.c -o mat_mult -lm -lgtb -I$(LLVM_BEACONS_PATH)/$(GTB_PATH) $(LDFLAGS)
.PHONY: all

clean:
	rm -f mat_mult 
.PHONY: clean
