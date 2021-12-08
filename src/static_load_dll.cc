#include <iostream>
#include "headers.h"
#include <Windows.h>

int main() {
    std::cout << "hello world\n";
    std::cout << "begin\n";
    curl(2);
    std::cout << "end\n";
    return 0;
}