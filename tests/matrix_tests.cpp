#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"
#include "matrix.hpp"
#include "tests_common.hpp"

using namespace cml;

TEST_CASE_TEMPLATE("Matrix: default constructor", T, ARITHMETIC_TYPES) {
    constexpr auto ROWS = 3;
    constexpr auto COLS = 2;
    Matrix<ROWS, COLS, T> a;

    for (auto i = 0u; i < ROWS; i++) {
        for (auto j = 0u; j < COLS; j++) {
            CHECK(a.get(i, j) == T());
        }
    }
}

TEST_CASE_TEMPLATE("Matrix: initializer list constructor", T,
                   ARITHMETIC_TYPES) {
    Matrix<3, 2, T> a{T(0), T(1), T(2), T(3), T(4), T(5)};

    for (auto i = 0u; i < 3; i++) {
        for (auto j = 0u; j < 2; j++) {
            CHECK(a.get(i, j) == i * 2 + j);
        }
    }
}

TEST_CASE_TEMPLATE("Matrix: iterator", T, ARITHMETIC_TYPES) {
    Matrix<3, 2, T> a{T(0), T(1), T(2), T(3), T(4), T(5)};

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

TEST_CASE_TEMPLATE("Matrix: copy", T, ARITHMETIC_TYPES) {
    constexpr auto ROWS = 3;
    constexpr auto COLS = 2;
    Matrix<ROWS, COLS, T> a{};
    Matrix<ROWS, COLS, T> b = a;
    b.get(0, 0) = T(1);

    for (auto i = 0u; i < ROWS; i++) {
        for (auto j = 0u; j < COLS; j++) {
            CHECK(a.get(i, j) == T(0));
        }
    }
}

TEST_CASE_TEMPLATE("Matrix: operator []", T, ARITHMETIC_TYPES) {
    constexpr auto ROWS = 3;
    constexpr auto COLS = 2;
    Matrix<ROWS, COLS, T> a{};
    a[0][0] = T(1);

    for (auto i = 0u; i < ROWS; i++) {
        for (auto j = 0u; j < COLS; j++) {
            CHECK(a.get(i, j) == a[i][j]);
        }
    }
}

TEST_CASE_TEMPLATE("Matrix: transposed", T, ARITHMETIC_TYPES) {
    constexpr auto ROWS = 3;
    constexpr auto COLS = 2;
    Matrix<ROWS, COLS, T> a{T(0), T(1), T(2), T(3), T(4), T(5)};

    Matrix<COLS, ROWS, T> b = a.transposed();

    for (auto i = 0u; i < 2; i++) {
        for (auto j = 0u; j < 3; j++) {
            CHECK(b.get(i, j) == a.get(j, i));
        }
    }
}

TEST_CASE_TEMPLATE("Matrix: operator unary -", T, ARITHMETIC_TYPES) {
    constexpr auto ROWS = 3;
    constexpr auto COLS = 2;
    Matrix<ROWS, COLS, T> a{T(0), T(1), T(2), T(3), T(4), T(5)};

    Matrix<ROWS, COLS, T> b = -a;

    for (auto i = 0u; i < ROWS; i++) {
        for (auto j = 0u; j < COLS; j++) {
            CHECK(a.get(i, j) == -b.get(i, j));
        }
    }
}

TEST_CASE_TEMPLATE("Matrix: operator +", T, ARITHMETIC_TYPES) {
    constexpr auto ROWS = 3;
    constexpr auto COLS = 2;
    Matrix<ROWS, COLS, T> a{T(0), T(1), T(2), T(3), T(4), T(5)};
    Matrix<ROWS, COLS, T> b{T(0), T(1), T(2), T(3), T(4), T(5)};

    Matrix<ROWS, COLS, T> c = a + b;

    for (auto i = 0u; i < ROWS; i++) {
        for (auto j = 0u; j < COLS; j++) {
            CHECK(c.get(i, j) == a.get(i, j) + b.get(i, j));
        }
    }
}

TEST_CASE_TEMPLATE("Matrix: operator +=", T, ARITHMETIC_TYPES) {
    constexpr auto ROWS = 3;
    constexpr auto COLS = 2;
    Matrix<ROWS, COLS, T> a{T(0), T(1), T(2), T(3), T(4), T(5)};
    Matrix<ROWS, COLS, T> b{T(0), T(1), T(2), T(3), T(4), T(5)};

    a += b;

    for (auto i = 0u; i < ROWS; i++) {
        for (auto j = 0u; j < COLS; j++) {
            CHECK(a.get(i, j) == 2 * b.get(i, j));
        }
    }
}

TEST_CASE_TEMPLATE("Matrix: operator binary -", T, ARITHMETIC_TYPES) {
    constexpr auto ROWS = 3;
    constexpr auto COLS = 2;
    Matrix<ROWS, COLS, T> a{T(0), T(1), T(2), T(3), T(4), T(5)};
    Matrix<ROWS, COLS, T> b{T(0), T(1), T(2), T(3), T(4), T(5)};

    Matrix<ROWS, COLS, T> c = a - b;

    for (auto i = 0u; i < ROWS; i++) {
        for (auto j = 0u; j < COLS; j++) {
            CHECK(c.get(i, j) == a.get(i, j) - b.get(i, j));
        }
    }
}

TEST_CASE_TEMPLATE("Matrix: operator -=", T, ARITHMETIC_TYPES) {
    constexpr auto ROWS = 3;
    constexpr auto COLS = 2;
    Matrix<ROWS, COLS, T> a{T(0), T(1), T(2), T(3), T(4), T(5)};
    Matrix<ROWS, COLS, T> b{T(0), T(1), T(2), T(3), T(4), T(5)};

    a -= b;

    for (auto i = 0u; i < ROWS; i++) {
        for (auto j = 0u; j < COLS; j++) {
            CHECK(a.get(i, j) == 0);
        }
    }
}

TEST_CASE_TEMPLATE("Matrix: operator * by another matrix", T,
                   ARITHMETIC_TYPES) {
    constexpr auto ROWS = 3;
    constexpr auto COLS = 2;
    constexpr auto RHCOLS = 4;
    Matrix<ROWS, COLS, T> a{T(0), T(1), T(2), T(3), T(4), T(5)};
    Matrix<COLS, RHCOLS, T> b{0, 1, 2, 3, 4, 5, 6, 7};

    Matrix<ROWS, RHCOLS, T> c = a * b;

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

TEST_CASE_TEMPLATE("Matrix: identity", T, ARITHMETIC_TYPES) {
    constexpr auto N = 3;
    auto id = Matrix<N, N, T>::identity();
    Matrix<N, N, T> a{0, 1, 2, 3, 4, 5, 6, 7, 8};
    Matrix<N, N, T> b = a * id;

    for (auto i = 0u; i < N; i++) {
        for (auto j = 0u; j < N; j++) {
            CHECK(a.get(i, j) == b.get(i, j));
        }
    }
}

TEST_CASE_TEMPLATE("Matrix: operator * by a scalar", T, ARITHMETIC_TYPES) {
    constexpr auto ROWS = 3;
    constexpr auto COLS = 2;
    constexpr auto SCALAR = 2;
    Matrix<ROWS, COLS, T> a{T(0), T(1), T(2), T(3), T(4), T(5)};

    Matrix<ROWS, COLS, T> b = a * SCALAR;

    for (auto i = 0u; i < ROWS; i++) {
        for (auto j = 0u; j < COLS; j++) {
            CHECK(b.get(i, j) == a.get(i, j) * SCALAR);
        }
    }
}
