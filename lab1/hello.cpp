
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <cstring>
#include <string>
#include "hello.h"

using namespace std;


std::pair<const char*, int> parse_args(int argc, char* argv[]) {
    switch (argc) {
        case 1:
            return std::make_pair("world", 1);
        
        case 2:
            return std::make_pair(argv[1], 1);
        
        case 3:
            try {
                int count = std::stoi(argv[2]);
                if (count < 0) {
                    cerr << "error: 2nd argument must be an integral greater than zero!" << endl;
                    return std::make_pair("", -1);
                }
                return std::make_pair(argv[1], count);
            } catch (...) {
                cerr << "error: 2nd argument must be an integral greater than zero!" << endl;
                return std::make_pair("", -1);
            }
        
        default:
            cerr << "error: Too many arguments!" << endl;
            return std::make_pair("", -1);
    }
}

void hello(const char* name, int count) {
    if (count == 0) {
        return;
    } else {
        cout << "Hello,";
        for (int i = 0; i < count; i++) {
            cout << " " << name;
        }
        cout << "!" << endl;
    }
}