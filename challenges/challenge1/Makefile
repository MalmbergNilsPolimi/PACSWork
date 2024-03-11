# Variables
INCLUDE_DIR := ./include
JSON_INCLUDE_DIR := ./lib/json/include
SRC_DIR := ./src
OBJ_DIR := ./obj
BIN_DIR := ./bin
MAIN_SRC := $(SRC_DIR)/main.cpp
JSON_PARSER_SRC := $(SRC_DIR)/json_parser.cpp
SEARCH_MIN_SRC := $(SRC_DIR)/search_min.cpp
MAIN_OBJ := $(OBJ_DIR)/main.o
JSON_PARSER_OBJ := $(OBJ_DIR)/json_parser.o
SEARCH_MIN_OBJ := $(OBJ_DIR)/search_min.o
EXECUTABLE := $(BIN_DIR)/main

# Compilation
$(EXECUTABLE): $(MAIN_OBJ) $(JSON_PARSER_OBJ) $(SEARCH_MIN_OBJ)
	@echo "Linking..."
	@mkdir -p $(BIN_DIR)
	@g++ -o $@ $^

$(OBJ_DIR)/main.o: $(MAIN_SRC)
	@echo "Compiling $<..."
	@mkdir -p $(OBJ_DIR)
	@g++ -o $@ -c $< -I$(INCLUDE_DIR) -I$(JSON_INCLUDE_DIR)

$(OBJ_DIR)/json_parser.o: $(JSON_PARSER_SRC)
	@echo "Compiling $<..."
	@mkdir -p $(OBJ_DIR)
	@g++ -o $@ -c $< -I$(INCLUDE_DIR) -I$(JSON_INCLUDE_DIR)

$(OBJ_DIR)/search_min.o: $(SEARCH_MIN_SRC)
	@echo "Compiling $<..."
	@mkdir -p $(OBJ_DIR)
	@g++ -o $@ -c $< -I$(INCLUDE_DIR) -I$(JSON_INCLUDE_DIR)

# Clean
clean:
	@echo "Cleaning..."
	@rm -rf $(OBJ_DIR) $(BIN_DIR)

# Phony targets
.PHONY: clean