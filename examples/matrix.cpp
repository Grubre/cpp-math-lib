#include "matrix.hpp"
#include <iostream>

int main() {
    Matrix<2, 2> a;
    // a[0][0] = 1;

    auto b = -a;
    auto c = b;

    b += a;
    b = b - c;
    b = b * a;
    std::cout << b[0][0] << std::endl;

    a[1][0] = 1;
    // a.get(1, 0) = 1;
    std::cout << a << std::endl;
    return 0;
}
