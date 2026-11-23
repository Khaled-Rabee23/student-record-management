CXX ?= g++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -O2
BUILD_DIR := build

.PHONY: all run-fixed run-variable clean

all: $(BUILD_DIR)/fixed_length $(BUILD_DIR)/variable_length

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/fixed_length: src/fixed_length.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@

$(BUILD_DIR)/variable_length: src/variable_length.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@

run-fixed: $(BUILD_DIR)/fixed_length
	./$(BUILD_DIR)/fixed_length

run-variable: $(BUILD_DIR)/variable_length
	./$(BUILD_DIR)/variable_length

clean:
	rm -rf $(BUILD_DIR)
