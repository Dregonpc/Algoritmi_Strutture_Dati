CC = gcc
CFLAGS = -g -Wall -Wextra -DUNITY_INCLUDE_DOUBLE -DUNITY_OUTPUT_COLOR

# Directories
BIN := bin
SRC := src
BLD := build
SHD := shared

# Crea le directory se non esistono
$(shell mkdir -p $(BIN) $(BLD))

default: all

all: $(BIN)/merge_sort_test $(BIN)/quick_sort_test

# Es1: Merge sort test
$(BIN)/merge_sort_test: $(BLD)/unity.o $(BLD)/compare.o $(BLD)/merge_sort.o $(BLD)/merge_sort_test.o
	$(CC) $(CFLAGS) $^ -o $@

$(BLD)/unity.o: $(SRC)/test/Unity/unity.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BLD)/compare.o: $(SRC)/$(SHD)/compare.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BLD)/merge_sort.o: $(SRC)/main/ex1/merge_sort.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BLD)/merge_sort_test.o: $(SRC)/test/merge_sort_test.c
	$(CC) $(CFLAGS) -c $< -o $@

# Es1: quick sort
$(BIN)/quick_sort_test: $(BLD)/unity.o $(BLD)/compare.o $(BLD)/quick_sort.o $(BLD)/quick_sort_test.o
	$(CC) $(CFLAGS) $^ -o $@

$(BLD)/quick_sort.o: $(SRC)/main/ex1/quick_sort.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BLD)/quick_sort_test.o: $(SRC)/test/quick_sort_test.c
	$(CC) $(CFLAGS) -c $< -o $@

# Pulizia delle cartelle create in precedenza
clean:
	rm -rf $(BLD) $(BIN)
