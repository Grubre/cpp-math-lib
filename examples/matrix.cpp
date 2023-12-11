#include "matrix.hpp"
#include "vec_mat_operations.hpp"
#include "vector.hpp"
#include <iostream>
#include <numeric>

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

    auto test = *(cml::ColumnVec<double, 3> *)&x;

    std::cout << test << std::endl;

    std::cout << C * test << std::endl;
    std::cout << C * x << std::endl;

    std::cout << "========================================\n";

    cml::Matrix<3, 3> D;
    std::iota(D.begin(), D.end(), 0);
    cml::Vec3<double> y;
    std::iota(y.begin(), y.end(), 0);

    cml::Matrix<4, 4> E;

    cml::rotate(E, 0.0, cml::Vec3d(0.0, 0.0, 0.0));

    std::cout << D;
    std::cout << y << std::endl;
    std::cout << D * y;

    return 0;
}
