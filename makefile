# Compiler and executable
CXX := g++
TARGET := arkanoid
BUILD_DIR := build

# Sanitizer flags (pour le débogage)
SANITIZER_FLAGS := -fsanitize=address,undefined -fno-omit-frame-pointer

# Warning flags (ensemble raisonnable)
WARN_FLAGS := -Wall -Wextra -pedantic -Wconversion -Wshadow -Wcast-align -Wunused -Wno-ignored-qualifiers

# Compiler flags
CXXFLAGS := -std=c++17 $(WARN_FLAGS) -g -Iinclude
LDFLAGS := 

# Allegro libraries
LDLIBS := -lallegro -lallegro_primitives -lallegro_font -lallegro_ttf -lallegro_main

EXCLUDE_FILES := src/ancienmain.cpp src/main2.cpp
# Source files (recursive find)
ALL_SRCS := $(shell find src -name "*.cpp")
SRCS := $(filter-out $(EXCLUDE_FILES), $(ALL_SRCS))
OBJS := $(SRCS:%.cpp=$(BUILD_DIR)/%.o)

# Default target
.PHONY: all
all: $(BUILD_DIR)/$(TARGET)

# Debug target avec sanitizers
.PHONY: debug
debug: CXXFLAGS += $(SANITIZER_FLAGS)
debug: LDFLAGS += $(SANITIZER_FLAGS)
debug: all

# Link executable
$(BUILD_DIR)/$(TARGET): $(OBJS)
	@mkdir -p $(@D)
	$(CXX) $(LDFLAGS) $^ -o $@ $(LDLIBS)

# Compile objects
$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -MMD -c $< -o $@

# Include auto-generated dependencies
-include $(OBJS:.o=.d)

# Clean build artifacts
.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)

# Rebuild from scratch
.PHONY: re
re: clean all