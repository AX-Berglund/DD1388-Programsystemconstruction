CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11
TARGET = hello_test
SRC = hello.cpp
TEST_SRC = tests/test_main.cpp

all: $(TARGET)

$(TARGET): $(SRC) $(TEST_SRC)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile the main program
hello: $(SRC) main.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

# Run tests
test: $(TARGET)
	./$(TARGET)

# Clean up
clean:
	rm -f $(TARGET) hello *.o

.PHONY: all test clean