#include <iostream>
#include "test_a.h"
#include "test_b.h"

int main() {
    std::cout << "---- Start Testing..." << std::endl;

    int x = 2 + 2;
    std::cout << "2 + 2 = " << x << std::endl;

    // Run tests.
    test_a();
    test_b();

    std::cout << "---- Finished Testing!" << std::endl;
    return 0;
}
