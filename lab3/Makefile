# Makefile for Matrix Class project

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic

# Main program
MAIN_TARGET = matrix_demo
MAIN_SOURCES = main.cpp
MAIN_OBJECTS = $(MAIN_SOURCES:.cpp=.o)

# Test program
TEST_TARGET = matrix_test
TEST_SOURCES = test_matrix.cpp
TEST_OBJECTS = $(TEST_SOURCES:.cpp=.o)

# Default target (builds everything)
all: $(MAIN_TARGET) $(TEST_TARGET)

# Main program build
$(MAIN_TARGET): $(MAIN_OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Test program build
$(TEST_TARGET): $(TEST_OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Generic rule for object files
%.o: %.cpp Matrix.h
	$(CXX) $(CXXFLAGS) -c $<

# Clean up
clean:
	rm -f $(MAIN_OBJECTS) $(TEST_OBJECTS) $(MAIN_TARGET) $(TEST_TARGET)

# Run main program
run: $(MAIN_TARGET)
	./$(MAIN_TARGET)

# Run test program
test: $(TEST_TARGET)
	./$(TEST_TARGET)

# Help target
help:
	@echo "Available targets:"
	@echo "  all        - Build both main program and test suite"
	@echo "  $(MAIN_TARGET)    - Build only the main demo program"
	@echo "  $(TEST_TARGET)    - Build only the test suite"
	@echo "  run        - Run the main demo program"
	@echo "  test       - Run the test suite"
	@echo "  clean      - Remove all build files"
	@echo "  help       - Display this help message"

test_reset: test_reset.cpp Matrix.h
	$(CXX) $(CXXFLAGS) test_reset.cpp -o test_reset

.PHONY: clean run

run: test_reset
	./test_reset

clean:
	rm -f test_reset