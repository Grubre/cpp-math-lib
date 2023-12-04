#include "vector.hpp"
#include <iostream>

int main() {
    Vec2i a{5, 6};

    Vec2i b = a;
    b.x = 1;
    std::cout << a << "  -  " << b << std::endl;
    return 0;
}
