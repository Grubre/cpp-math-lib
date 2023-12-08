#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"
#include "matrix.hpp"

using namespace cml;

TEST_CASE("Matrix: default constructor") {
    constexpr auto ROWS = 3;
    constexpr auto COLS = 2;
    Matrix<ROWS, COLS, int> a{};

    for (auto i = 0u; i < ROWS; i++) {
        for (auto j = 0u; j < COLS; j++) {
            CHECK(a.get(i, j) == 0);
        }
    }
}

TEST_CASE("Matrix: initializer list constructor") {
    Matrix<3, 2, int> a{0, 1, 2, 3, 4, 5};

    for (auto i = 0u; i < 3; i++) {
        for (auto j = 0u; j < 2; j++) {
            CHECK(a.get(i, j) == i * 2 + j);
        }
    }
}

TEST_CASE("Matrix: iterator") {
    Matrix<3, 2, int> a{0, 1, 2, 3, 4, 5};

    for (auto &x : a) {
        x *= 2;
    }

    auto it = a.begin();
    for (auto i = 0u; i < 3; i++) {
        for (auto j = 0u; j < 2; j++) {
            CHECK(*it == i * 4 + 2 * j);
            it++;
        }
    }
}

TEST_CASE("Matrix: copy") {
    constexpr auto ROWS = 3;
    constexpr auto COLS = 2;
    Matrix<ROWS, COLS, int> a{};
    Matrix<ROWS, COLS, int> b = a;
    b.get(0, 0) = 1;

    for (auto i = 0u; i < ROWS; i++) {
        for (auto j = 0u; j < COLS; j++) {
            CHECK(a.get(i, j) == 0);
        }
    }
}

TEST_CASE("Matrix: operator []") {
    constexpr auto ROWS = 3;
    constexpr auto COLS = 2;
    Matrix<ROWS, COLS, int> a{};
    a[0][0] = 1;

    for (auto i = 0u; i < ROWS; i++) {
        for (auto j = 0u; j < COLS; j++) {
            CHECK(a.get(i, j) == a[i][j]);
        }
    }
}

TEST_CASE("Matrix: transposed") {
    constexpr auto ROWS = 3;
    constexpr auto COLS = 2;
    Matrix<ROWS, COLS> a{0, 1, 2, 3, 4, 5};

    Matrix<COLS, ROWS> b = a.transposed();

    for (auto i = 0u; i < 2; i++) {
        for (auto j = 0u; j < 3; j++) {
            CHECK(b.get(i, j) == a.get(j, i));
        }
    }
}

TEST_CASE("Matrix: operator unary -") {
    constexpr auto ROWS = 3;
    constexpr auto COLS = 2;
    Matrix<ROWS, COLS> a{0, 1, 2, 3, 4, 5};

    Matrix<ROWS, COLS> b = -a;

    for (auto i = 0u; i < ROWS; i++) {
        for (auto j = 0u; j < COLS; j++) {
            CHECK(a.get(i, j) == -b.get(i, j));
        }
    }
}

TEST_CASE("Matrix: operator +") {
    constexpr auto ROWS = 3;
    constexpr auto COLS = 2;
    Matrix<ROWS, COLS> a{0, 1, 2, 3, 4, 5};
    Matrix<ROWS, COLS> b{0, 1, 2, 3, 4, 5};

    Matrix<ROWS, COLS> c = a + b;

    for (auto i = 0u; i < ROWS; i++) {
        for (auto j = 0u; j < COLS; j++) {
            CHECK(c.get(i, j) == a.get(i, j) + b.get(i, j));
        }
    }
}

TEST_CASE("Matrix: operator +=") {
    constexpr auto ROWS = 3;
    constexpr auto COLS = 2;
    Matrix<ROWS, COLS> a{0, 1, 2, 3, 4, 5};
    Matrix<ROWS, COLS> b{0, 1, 2, 3, 4, 5};

    a += b;

    for (auto i = 0u; i < ROWS; i++) {
        for (auto j = 0u; j < COLS; j++) {
            CHECK(a.get(i, j) == 2 * b.get(i, j));
        }
    }
}

TEST_CASE("Matrix: operator binary -") {
    constexpr auto ROWS = 3;
    constexpr auto COLS = 2;
    Matrix<ROWS, COLS> a{0, 1, 2, 3, 4, 5};
    Matrix<ROWS, COLS> b{0, 1, 2, 3, 4, 5};

    Matrix<ROWS, COLS> c = a - b;

    for (auto i = 0u; i < ROWS; i++) {
        for (auto j = 0u; j < COLS; j++) {
            CHECK(c.get(i, j) == a.get(i, j) - b.get(i, j));
        }
    }
}

TEST_CASE("Matrix: operator -=") {
    constexpr auto ROWS = 3;
    constexpr auto COLS = 2;
    Matrix<ROWS, COLS> a{0, 1, 2, 3, 4, 5};
    Matrix<ROWS, COLS> b{0, 1, 2, 3, 4, 5};

    a -= b;

    for (auto i = 0u; i < ROWS; i++) {
        for (auto j = 0u; j < COLS; j++) {
            CHECK(a.get(i, j) == 0);
        }
    }
}

TEST_CASE("Matrix: operator * by another matrix") {
    constexpr auto ROWS = 3;
    constexpr auto COLS = 2;
    constexpr auto RHCOLS = 4;
    Matrix<ROWS, COLS> a{0, 1, 2, 3, 4, 5};
    Matrix<COLS, RHCOLS> b{0, 1, 2, 3, 4, 5, 6, 7};

    Matrix<ROWS, RHCOLS> c = a * b;

    for (auto row = 0u; row < ROWS; row++) {
        for (auto col = 0u; col < RHCOLS; col++) {
            auto sum = 0;
            for (auto k = 0u; k < COLS; k++) {
                sum += a.get(row, k) * b.get(k, col);
            }
            CHECK(c.get(row, col) == sum);
        }
    }
}

TEST_CASE("Matrix: identity") {
    constexpr auto N = 3;
    auto id = Matrix<N, N>::identity();
    Matrix<N, N> a{0, 1, 2, 3, 4, 5, 6, 7, 8};
    Matrix<N, N> b = a * id;

    for (auto i = 0u; i < N; i++) {
        for (auto j = 0u; j < N; j++) {
            CHECK(a.get(i, j) == b.get(i, j));
        }
    }
}

TEST_CASE("Matrix: operator * by a scalar") {
    constexpr auto ROWS = 3;
    constexpr auto COLS = 2;
    constexpr auto SCALAR = 2;
    Matrix<ROWS, COLS> a{0, 1, 2, 3, 4, 5};

    Matrix<ROWS, COLS> b = a * SCALAR;

    for (auto i = 0u; i < ROWS; i++) {
        for (auto j = 0u; j < COLS; j++) {
            CHECK(b.get(i, j) == a.get(i, j) * SCALAR);
        }
    }
}
