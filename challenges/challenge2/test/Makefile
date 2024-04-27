# Compiler
CXX = g++
# Compiler flags
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic -I../include
# Source files
SRCS = test_compress.cpp test_marketReader.cpp test_multiply.cpp test_resize.cpp
# Object files directory
OBJ_DIR = obj
# Binary files directory
BIN_DIR = bin

# Object files list (replace .cpp extension with .o)
OBJS = $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(SRCS))

# Default target
.PHONY: all
all: directories compress marketReader multiply resize

# Rule for creating directories
directories:
	mkdir -p $(OBJ_DIR)
	mkdir -p $(BIN_DIR)

# Rule for compiling all source files
$(OBJ_DIR)/%.o: %.cpp | directories
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule for building compress
compress: $(OBJ_DIR)/test_compress.o
	$(CXX) $(CXXFLAGS) $(OBJ_DIR)/test_compress.o -o $(BIN_DIR)/compress

# Rule for building marketReader
marketReader: $(OBJ_DIR)/test_marketReader.o
	$(CXX) $(CXXFLAGS) $(OBJ_DIR)/test_marketReader.o -o $(BIN_DIR)/marketReader

# Rule for building multiply
multiply: $(OBJ_DIR)/test_multiply.o
	$(CXX) $(CXXFLAGS) $(OBJ_DIR)/test_multiply.o -o $(BIN_DIR)/multiply

# Rule for building resize
resize: $(OBJ_DIR)/test_resize.o
	$(CXX) $(CXXFLAGS) $(OBJ_DIR)/test_resize.o -o $(BIN_DIR)/resize

# Rule for running a specific target
.PHONY: run
run: $(BIN_DIR)
	@echo "Usage: make run [target]"
	@echo "Available targets: compress, marketReader, multiply, resize"

run_compress: $(BIN_DIR)/compress
	./$(BIN_DIR)/compress

run_marketReader: $(BIN_DIR)/marketReader
	./$(BIN_DIR)/marketReader

run_multiply: $(BIN_DIR)/multiply
	./$(BIN_DIR)/multiply

run_resize: $(BIN_DIR)/resize
	./$(BIN_DIR)/resize

# Rule for cleaning up
.PHONY: clean
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)