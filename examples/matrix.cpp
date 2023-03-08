#include <iostream>
#include "matrix.hpp"

int main() {
    Matrix<2, 2> a;
    a(0,0) = 1;
    auto b = -a;
    auto c = b;
    b += a;
    b = b - c;
    b = b * a;
    std::cout << a(0,0) << std::endl;
    std::cout << b(0,0) << std::endl;
    return 0;
}
