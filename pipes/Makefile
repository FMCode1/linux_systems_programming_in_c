# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -g

# Executable name
TARGET = demo

# Default rule
all: $(TARGET)

# Build the program
$(TARGET): pipes.cpp
	$(CXX) $(CXXFLAGS) pipes.cpp -o $(TARGET)

# Clean build files
clean:
	rm -f $(TARGET)