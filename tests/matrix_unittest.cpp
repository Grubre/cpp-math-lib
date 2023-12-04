#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"
#include "matrix.hpp"

TEST_CASE("Matrix: default constructor") {
    Matrix<3, 2, int> a{};
    CHECK(a.get(0, 0) == 0);
    CHECK(a.get(0, 1) == 0);
    CHECK(a.get(1, 0) == 0);
    CHECK(a.get(1, 1) == 0);
    CHECK(a.get(2, 0) == 0);
    CHECK(a.get(2, 1) == 0);
}

TEST_CASE("Matrix: copy") {
    Matrix<3, 2, int> a{};
    Matrix<3, 2, int> b = a;
    b.get(0, 0) = 1;
    CHECK(a.get(0, 0) != b.get(0, 0));
    CHECK(a.get(0, 1) == b.get(0, 1));
    CHECK(a.get(1, 0) == b.get(1, 0));
    CHECK(a.get(1, 1) == b.get(1, 1));
    CHECK(a.get(2, 0) == b.get(2, 0));
    CHECK(a.get(2, 1) == b.get(2, 1));
}

TEST_CASE("Matrix: operator []") {
    Matrix<3, 2, int> a{};
    a[0][0] = 1;
    CHECK(a.get(0, 0) == a[0][0]);
    CHECK(a.get(1, 0) == a[1][0]);
    CHECK(a.get(0, 1) == a[0][1]);
    CHECK(a.get(1, 1) == a[1][1]);
    CHECK(a.get(0, 2) == a[0][2]);
    CHECK(a.get(1, 2) == a[1][2]);
}

TEST_CASE("Matrix: transposed") {
    Matrix<2, 3> a{0, 1, 2, 3, 4, 5};

    Matrix<3, 2> b = a.transposed();

    for (auto i = 0u; i < 2; i++) {
        for (auto j = 0u; j < 3; j++) {
            CHECK(a.get(i, j) == b.get(j, i));
        }
    }
}
