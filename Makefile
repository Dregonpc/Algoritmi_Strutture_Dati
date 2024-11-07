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

all: $(BIN)/merge_sort_test $(BIN)/quick_sort_test $(BIN)/test_ex1 $(BIN)/main_ex1

# Es1: Merge sort tests
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

# Es1: Quick sort tests
$(BIN)/quick_sort_test: $(BLD)/unity.o $(BLD)/compare.o $(BLD)/quick_sort.o $(BLD)/quick_sort_test.o
	$(CC) $(CFLAGS) $^ -o $@

$(BLD)/quick_sort.o: $(SRC)/main/ex1/quick_sort.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BLD)/quick_sort_test.o: $(SRC)/test/quick_sort_test.c
	$(CC) $(CFLAGS) -c $< -o $@

# Es1: Merge + Quick sort tests
$(BIN)/test_ex1: $(BLD)/unity.o $(BLD)/compare.o $(BLD)/merge_sort.o $(BLD)/quick_sort.o $(BLD)/test_ex1.o
	$(CC) $(CFLAGS) $^ -o $@

$(BLD)/test_ex1.o: $(SRC)/test/test_ex1.c
	$(CC) $(CFLAGS) -c $< -o $@

# Es1: main_ex1
$(BIN)/main_ex1: $(BLD)/record.o $(BLD)/quick_sort.o $(BLD)/merge_sort.o $(BLD)/main_ex1.o
	$(CC) $(CFLAGS) $^ -o $@

$(BLD)/record.o: $(SRC)/main/ex1/record.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BLD)/main_ex1.o: $(SRC)/main/ex1/main_ex1.c
	$(CC) $(CFLAGS) -c $< -o $@

# Pulizia delle cartelle create in precedenza
clean:
	rm -rf $(BLD) $(BIN)
