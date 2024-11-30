CC = gcc
CFLAGS = -g -Wall -Wextra -DUNITY_OUTPUT_COLOR

# Directories
SRC := src
BIN := bin
BLD := build
TEST := test

$(shell mkdir -p $(BIN) $(BLD))

default: all

all: $(BIN)/test_ex2 $(BIN)/main_ex2 

# Es2: Unit test
$(BIN)/test_ex2: $(BLD)/unity.o $(BLD)/distance.o $(BLD)/test_ex2.o
	$(CC) $(CFLAGS) $^ -o $@

$(BLD)/unity.o: ../../$(TEST)/Unity/unity.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BLD)/distance.o: $(SRC)/distance.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BLD)/test_ex2.o: ../../$(TEST)/test_ex2.c
	$(CC) $(CFLAGS) -c $< -o $@

#Es2 : Main
$(BIN)/main_ex2: $(BLD)/distance.o $(BLD)/main_ex2.o
	$(CC) $(CFLAGS) $^ -o $@

$(BLD)/main_ex2.o: $(SRC)/main_ex2.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BLD) $(BIN)