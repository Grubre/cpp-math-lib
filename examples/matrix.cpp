#include "matrix.hpp"
#include "vector.hpp"
#include <iostream>

int main() {
    cml::Matrix<2, 3, double> A = {0., 4., -2., -4., -3., 0.};
    cml::Matrix<3, 2, double> B = {0., 1., 1., -1., 2., 3.};

    std::cout << A << std::endl;
    std::cout << B << std::endl;
    std::cout << A * B << std::endl;

    cml::Matrix<2, 3, double> C = {1., -1., 2., 0., -3., 1.};
    cml::Vec3d x = {2., 1., 0.};

    std::cout << A << std::endl;
    std::cout << x << std::endl;

    auto test = *(cml::Matrix<3, 1, double> *)&x;

    std::cout << test << std::endl;

    std::cout << C * test << std::endl;

    return 0;
}
