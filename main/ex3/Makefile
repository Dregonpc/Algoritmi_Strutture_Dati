CC = gcc
CFLAGS = -g -Wall -Wextra -DUNITY_OUTPUT_COLOR

# Directories
SRC := src
BIN := bin
BLD := build
TEST := test

$(shell mkdir -p $(BIN) $(BLD))

default: all

all: $(BIN)/main_ex3 $(BIN)/test_ex3

#Es3: Main
$(BIN)/main_ex3: $(BLD)/hash_table.o $(BLD)/main_ex3.o
	$(CC) $(CFLAGS) $^ -o $@

$(BLD)/hash_table.o: $(SRC)/hash_table.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BLD)/main_ex3.o: $(SRC)/main_ex3.c
	$(CC) $(CFLAGS) -c $< -o $@

# Es3: Unit test
$(BIN)/test_ex3: $(BLD)/unity.o $(BLD)/hash_table.o $(BLD)/test_ex3.o
	$(CC) $(CFLAGS) $^ -o $@

$(BLD)/unity.o: ../../$(TEST)/Unity/unity.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BLD)/test_ex3.o: ../../$(TEST)/test_ex3.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BLD) $(BIN)