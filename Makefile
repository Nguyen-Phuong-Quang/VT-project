# Makefile

# Compiler
CXX := g++
# Compiler flags
CXXFLAGS := -Wall -Wextra -std=c++14

# Folder contains source code
SRC_DIR := RTOS

# Find all source code *.cpp inside RTOS
SRCS := $(wildcard $(SRC_DIR)/*.cpp)

# Create object file corresponding to source code
OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(SRC_DIR)/%.o, $(SRCS))

# Create execute file
TARGET := main

all: $(TARGET)

$(TARGET): $(OBJS) main.o
	$(CXX) $(CXXFLAGS) $^ -o $@

$(SRC_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(SRC_DIR)/*.o $(TARGET) $(TARGET).o
