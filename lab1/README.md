# Assignment 1: Compilation pipeline, tooling

## Problem A: Hello World

You shall upload a single source file named `hello.cpp`, containing the definition of two functions:
- `parse_args(int argc, char *argv[])`
- `hello(const char *name, int count)`

## Requirements

### `parse_args`
- Responsible for parsing/interpreting the command-line arguments passed to the application.
- Returns a `std::pair` with:
    - What to print.
    - How many times to print it.
- Handles all input errors by:
    - Returning `-1` as the second value of the returned `std::pair`.
    - Printing a suitable error message to `stderr`.

### `hello`
- Responsible for printing the hello world string to `stdout` with the following semantics:
    - If the value `0` is passed as the second parameter, nothing shall be printed.
    - If a value greater than `0` is passed as the second argument (`count`), `"Hello, "` shall be printed followed by `count` space-delimited occurrences of the first argument.
- The output shall end with an exclamation mark (`!`), followed by a newline.

**Note:**  
`hello("KTH", 3)` shall print:  
```
Hello, KTH KTH KTH!
```

### Output Rules
- Correct output from your program shall be printed through `std::cout`.
- Potential error diagnostics (detected by `parse_args`) shall be printed through `std::cerr`.
- Error messages shall start with the word `error`, followed by the error message.

## Sample Output

```bash
> ./hello
Hello, world!

> ./hello "DD1387"
Hello, DD1387!

> ./hello "KTH" 3
Hello, KTH KTH KTH!

> ./hello "KTH" 0

> ./hello "KTH" 2
Hello, KTH KTH!

> ./hello "Malcom X" NaN
error: 2nd argument must be an integral greater than zero!

> ./hello kth dd1387 3
error: Too many arguments!
```

## How to Compile

### Using Make

```bash
# Compile the main program
make hello

# Compile test suite
make
```

### Manual Compilation

```bash
# Compile the main program
g++ -Wall -Wextra -std=c++11 -o hello hello.cpp main.cpp

# Compile test suite
g++ -Wall -Wextra -std=c++11 -o hello_test hello.cpp tests/test_main.cpp
```

## How to Run

### Running the Program

```bash
# Default behavior
./hello

# With custom name
./hello "DD1387"

# With custom name and repetition count
./hello "KTH" 3
```

### Running Tests

```bash
# Using make
make test

# Or run directly
./hello_test
```

## Test Cases

The test suite covers:
- Default behavior with no arguments
- Custom name with one argument
- Multiple repetitions of the name
- Zero repetition (should print nothing)
- Invalid inputs (non-integer count, negative count)
- Too many arguments

## Kattis Link

[Link to the problem on Kattis](https://kth.kattis.com/courses/DD1387/problem-abc)