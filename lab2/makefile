# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++11 -Wall -Wextra -g

# Executable names
EXECUTABLES = ComplexKattisTest ComplexExtendedTest ComplexTest ComplexBugFinder ComplexDivisionTest ComplexScalarDivTest

# Source files
SOURCES = Complex.cpp

# Test source files
KATTIS_TEST = ComplexKattisTest.cpp
EXTENDED_TEST = ComplexExtendedTest.cpp
BASIC_TEST = ComplexTest.cpp
BUG_FINDER = ComplexBugFinder.cpp
DIVISION_TEST = ComplexDivisionTest.cpp
SCALAR_DIV_TEST = ComplexScalarDivTest.cpp
# Default target
all: $(EXECUTABLES)

# Build Kattis test
ComplexKattisTest: $(KATTIS_TEST) $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Build Extended test
ComplexExtendedTest: $(EXTENDED_TEST) $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Build Basic test
ComplexTest: $(BASIC_TEST) $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Build Bug finder
ComplexBugFinder: $(BUG_FINDER) $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $@ $^

ComplexDivisionTest: $(DIVISION_TEST) $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $@ $^

ComplexScalarDivTest: $(SCALAR_DIV_TEST) $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Clean up build files
clean:
	rm -f $(EXECUTABLES)