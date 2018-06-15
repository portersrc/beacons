
CC         := g++
CFLAGS     := -Wall -O3
CFLAGS_DBG := -Wall -g -O0 -DBSCHED_DBG
BIN = bsched

SRC    :=   $(shell find -type f -name \*.cpp -print)
OBJ    :=   $(patsubst %.cpp,%.o,$(SRC))

all: $(BIN)
.PHONY: all

debug: CFLAGS := $(CFLAGS_DBG)
debug: all

clean:
	@rm -f *.o $(BIN)
.PHONY: clean

$(BIN): $(OBJ)
	$(CC) -o $@ $^

$(OBJ): $(SRC)
	$(CC) $(CFLAGS) -c $< -o $@
