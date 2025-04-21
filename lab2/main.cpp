#include "Complex.h"
#include <iostream>

int main() {
    Complex a(3.0, 4.0);
    Complex b(1.0, 2.0);
    Complex c = a + b;

    std::cout << "a: " << a << std::endl;
    std::cout << "b: " << b << std::endl;
    std::cout << "c: " << c << std::endl;

    return 0;
} 