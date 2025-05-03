#include <utility>  // std::pair
#pragma once
void hello (const char * name, int count);
std::pair<const char *, int> parse_args (int argc, char * argv[]);