CC = gcc
CFLAGS = -g -Wall -Wextra -DUNITY_OUTPUT_COLOR

# Directories
SRC := src
BIN := bin
BLD := build
TEST := test

$(shell mkdir -p $(BIN) $(BLD))

default: all

all: $(BIN)/main_ex3-4 $(BIN)/test_ex3-4

#Es3-4: Main
$(BIN)/main_ex3-4: $(BLD)/hash_table.o $(BLD)/graph.o $(BLD)/main_ex3-4.o
	$(CC) $(CFLAGS) $^ -o $@

$(BLD)/hash_table.o: $(SRC)/hash_table.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BLD)/graph.o: $(SRC)/graph.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BLD)/main_ex3-4.o: $(SRC)/main_ex3-4.c
	$(CC) $(CFLAGS) -c $< -o $@

# Es3-4: Unit test
$(BIN)/test_ex3-4: $(BLD)/unity.o $(BLD)/hash_table.o $(BLD)/graph.o $(BLD)/test_ex3-4.o
	$(CC) $(CFLAGS) $^ -o $@

$(BLD)/unity.o: ../../$(TEST)/Unity/unity.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BLD)/test_ex3-4.o: ../../$(TEST)/test_ex3-4.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BLD) $(BIN)