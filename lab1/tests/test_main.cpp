#include <iostream>
#include <string>
#include <cassert>
#include <sstream>

// Include the function declarations
extern std::pair<const char*, int> parse_args(int argc, char* argv[]);
extern void hello(const char* name, int count);

// Capture standard output
class CaptureOutput {
private:
    std::streambuf* old_cout;
    std::stringstream buffer;
public:
    CaptureOutput() {
        old_cout = std::cout.rdbuf(buffer.rdbuf());
    }
    
    ~CaptureOutput() {
        std::cout.rdbuf(old_cout);
    }
    
    std::string get_output() {
        return buffer.str();
    }
};

// Capture standard error
class CaptureError {
private:
    std::streambuf* old_cerr;
    std::stringstream buffer;
public:
    CaptureError() {
        old_cerr = std::cerr.rdbuf(buffer.rdbuf());
    }
    
    ~CaptureError() {
        std::cerr.rdbuf(old_cerr);
    }
    
    std::string get_output() {
        return buffer.str();
    }
};

// Test hello function
void test_hello() {
    std::cout << "Testing hello function..." << std::endl;
    
    // Test case 1: Default "world"
    {
        CaptureOutput capture;
        hello("world", 1);
        assert(capture.get_output() == "Hello, world!\n");
    }
    
    // Test case 2: Custom name
    {
        CaptureOutput capture;
        hello("DD1387", 1);
        assert(capture.get_output() == "Hello, DD1387!\n");
    }
    
    // Test case 3: Multiple repetitions
    {
        CaptureOutput capture;
        hello("KTH", 3);
        assert(capture.get_output() == "Hello, KTH KTH KTH!\n");
    }
    
    // Test case 4: Zero count (should print nothing)
    {
        CaptureOutput capture;
        hello("KTH", 0);
        assert(capture.get_output() == "");
    }
    
    std::cout << "All hello tests passed!" << std::endl;
}

// Test parse_args function
void test_parse_args() {
    std::cout << "Testing parse_args function..." << std::endl;
    
    // Test case 1: No arguments
    {
        int argc = 1;
        char* argv[] = {(char*)"./hello", nullptr};
        auto result = parse_args(argc, argv);
        assert(std::string(result.first) == "world");
        assert(result.second == 1);
    }
    
    // Test case 2: One argument
    {
        int argc = 2;
        char* argv[] = {(char*)"./hello", (char*)"DD1387", nullptr};
        auto result = parse_args(argc, argv);
        assert(std::string(result.first) == "DD1387");
        assert(result.second == 1);
    }
    
    // Test case 3: Two arguments
    {
        int argc = 3;
        char* argv[] = {(char*)"./hello", (char*)"KTH", (char*)"3", nullptr};
        auto result = parse_args(argc, argv);
        assert(std::string(result.first) == "KTH");
        assert(result.second == 3);
    }
    
    // Test case 4: Two arguments with zero count
    {
        int argc = 3;
        char* argv[] = {(char*)"./hello", (char*)"KTH", (char*)"0", nullptr};
        auto result = parse_args(argc, argv);
        assert(std::string(result.first) == "KTH");
        assert(result.second == 0);
    }
    
    // Test case 5: Invalid count (NaN)
    {
        CaptureError capture;
        int argc = 3;
        char* argv[] = {(char*)"./hello", (char*)"KTH", (char*)"NaN", nullptr};
        auto result = parse_args(argc, argv);
        assert(result.second == -1);
        assert(capture.get_output().find("error: 2nd argument must be an integral greater than zero!") != std::string::npos);
    }
    
    // Test case 6: Too many arguments
    {
        CaptureError capture;
        int argc = 4;
        char* argv[] = {(char*)"./hello", (char*)"kth", (char*)"dd1387", (char*)"3", nullptr};
        auto result = parse_args(argc, argv);
        assert(result.second == -1);
        assert(capture.get_output().find("error: Too many arguments!") != std::string::npos);
    }
    
    std::cout << "All parse_args tests passed!" << std::endl;
}

int main() {
    test_hello();
    test_parse_args();
    std::cout << "All tests passed successfully!" << std::endl;
    return 0;
}