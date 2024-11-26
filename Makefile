# Compiler and flags
CC = gcc
CFLAGS = -O3 -march=native -Wall

# Directories
SRC_DIR = src
TOOLS_DIR = tools
TEST_DIR = test
ROOT_DIR = .

# Source files and object files
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
TOOLS_FILES = $(wildcard $(TOOLS_DIR)/*.c)
OBJ_FILES = $(SRC_FILES:.c=.o) $(TOOLS_FILES:.c=.o)

# Test files and executables
TEST_FILES = $(wildcard $(TEST_DIR)/*.c)
TEST_EXEC = $(patsubst $(TEST_DIR)/%.c, $(ROOT_DIR)/%, $(TEST_FILES))

# Default target: build all test executables
all: $(TEST_EXEC)

# Rule to compile source files into object files
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

# Rule to compile tools files into object files
$(TOOLS_DIR)/%.o: $(TOOLS_DIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

# Rule to compile each test executable
$(TEST_EXEC): $(OBJ_FILES) $(TEST_FILES)
	@for test_file in $(TEST_FILES); do \
		test_exec=$(ROOT_DIR)/$$(basename $$test_file .c); \
		echo "Building $$test_exec..."; \
		$(CC) $(CFLAGS) -o $$test_exec $(OBJ_FILES) $$test_file; \
	done

# Run all test executables
test: $(TEST_EXEC)
	@for exec in $(TEST_EXEC); do \
		echo "Running $$exec..."; \
		./$$exec || exit 1; \
	done

# Clean up object files and test executables
clean:
	rm -f $(OBJ_FILES) $(TEST_EXEC)

.PHONY: all clean test
