# Compiler and standard settings
CXX := g++
CXXFLAGS += -std=c++2b -pedantic -Wall -Wextra -g -O2
CXXFLAGS += -Walloc-zero -Wcast-align -Wconversion -Wctad-maybe-unsupported -Wctor-dtor-privacy
CXXFLAGS += -Wdeprecated-copy-dtor -Wduplicated-branches -Wduplicated-cond -Wextra-semi -Wfloat-equal
CXXFLAGS += -Wformat-signedness -Wformat=2 -Winit-self -Wlogical-op -Wmismatched-tags -Wnoexcept
CXXFLAGS += -Wnon-virtual-dtor -Wnull-dereference -Wold-style-cast -Woverloaded-virtual
CXXFLAGS += -Wredundant-tags -Wshadow -Wsign-promo -Wstrict-null-sentinel
CXXFLAGS += -Wsuggest-attribute=const -Wsuggest-attribute=noreturn 
CXXFLAGS += -Wsuggest-override -Wswitch-default -Wswitch-enum -Wundef
CXXFLAGS += -Wuseless-cast -Wvolatile -Wzero-as-null-pointer-constant

# Include directories for Allegro or other libraries
CXXFLAGS += $(shell pkg-config allegro-5 allegro_primitives-5 allegro_font-5 --cflags | sed 's/-I/-isystem/g')

# Sanitizer flags (add as needed)
SANITIZER_FLAGS := -fsanitize=address -g -fsanitize=undefined  \
 -fno-omit-frame-pointer -fsanitize-recover=all
                   
#-fsanitize=thread -fsanitize=memory

# Combine sanitizers with standard CXXFLAGS
CXXFLAGS += $(SANITIZER_FLAGS)

# Linker flags
LDLIBS += $(shell pkg-config allegro-5 allegro_primitives-5 allegro_font-5 allegro_ttf-5 --libs) -lallegro_main

# Executable name
TARGET := arkanoid

# Source files
SRCS := main.cpp Paddle.cpp Block.cpp Ball.cpp Level.cpp Score.cpp

# Object files (derived from source files)
OBJS := $(SRCS:.cpp=.o)

# Default rule
.PHONY: default
default: $(TARGET)

# Build target executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDLIBS)

# Compile source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up object files
.PHONY: clean
clean:
	rm -f $(OBJS)

# Clean up everything including the executable
.PHONY: mrclean
mrclean: clean
	rm -f $(TARGET)
