CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -I./include
SRC = src/assignment5.cpp
OBJ = build/assignment5.o
TARGET = build/assignment5

# Default target
all: $(TARGET)

# Build executable
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile object files
build/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Run the program
run: $(TARGET)
	./$(TARGET)

# Clean build artifacts
clean:
	rm -f $(OBJ) $(TARGET)

# Phony targets
.PHONY: all run clean
