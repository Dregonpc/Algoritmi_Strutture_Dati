CC = gcc
CFLAGS = -g -Wall -Wextra -DUNITY_INCLUDE_DOUBLE -DUNITY_OUTPUT_COLOR

# Directories
SRC := src
BIN := bin
BLD := build
TEST := test

$(shell mkdir -p $(BIN) $(BLD))

default: all

all: $(BIN)/test_ex1 $(BIN)/main_ex1

# Es1: test_es1
$(BIN)/test_ex1: $(BLD)/unity.o $(BLD)/compare.o $(BLD)/merge_sort.o $(BLD)/quick_sort.o $(BLD)/test_ex1.o
	$(CC) $(CFLAGS) $^ -o $@

$(BLD)/unity.o: ../../$(TEST)/Unity/unity.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BLD)/compare.o: $(SRC)/compare.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BLD)/merge_sort.o: $(SRC)/merge_sort.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BLD)/quick_sort.o: $(SRC)/quick_sort.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BLD)/test_ex1.o: ../../$(TEST)/test_ex1.c
	$(CC) $(CFLAGS) -c $< -o $@

# Es1: main_ex1
$(BIN)/main_ex1: $(BLD)/record.o $(BLD)/compare.o $(BLD)/quick_sort.o $(BLD)/merge_sort.o $(BLD)/main_ex1.o
	$(CC) $(CFLAGS) $^ -o $@

$(BLD)/record.o: $(SRC)/record.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BLD)/main_ex1.o: $(SRC)/main_ex1.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BLD) $(BIN)
