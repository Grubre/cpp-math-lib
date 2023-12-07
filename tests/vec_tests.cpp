#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"
#include "tests_common.hpp"
#include "vector.hpp"
#include <array>
#include <numeric>

using namespace cml;

#define TT typename T::Type

TEST_CASE_TEMPLATE("Vec: default constructor", T, ARITHMETIC_TYPES_AND_DIMS) {
    Vec<TT, T::dim> a;
    for (auto i = 0u; i < T::dim; i++) {
        CHECK(a[i] == TT(0));
    }
}

TEST_CASE_TEMPLATE("Vec: copy", T, ARITHMETIC_TYPES_AND_DIMS) {
    Vec<TT, T::dim> a;
    std::iota(a.begin(), a.end(), TT(0));

    Vec<TT, T::dim> b = a;
    for (auto i = 0u; i < T::dim; i++) {
        CHECK(a[i] == b[i]);
    }
}

TEST_CASE_TEMPLATE("Vec: constructor from lower dim", T, ARITHMETIC_TYPES_AND_DIMS) {
    Vec<TT, T::dim> a;
    std::iota(a.begin(), a.end(), TT(0));

    Vec<TT, T::dim + 1> b(a);
    for (auto i = 0u; i < T::dim; i++) {
        CHECK(a[i] == b[i]);
    }
}

TEST_CASE_TEMPLATE("Vec: constructor from higher dim", T, ARITHMETIC_TYPES_AND_DIMS) {
    Vec<TT, T::dim> a;
    std::iota(a.begin(), a.end(), TT(0));

    Vec<TT, T::dim - 1> b(a);
    for (auto i = 0u; i < T::dim - 1; i++) {
        CHECK(a[i] == b[i]);
    }
}

TEST_CASE_TEMPLATE("Vec: operator []", T, ARITHMETIC_TYPES_AND_DIMS) {
    Vec<TT, T::dim> a;
    auto values = std::array<TT, T::dim>{};
    std::iota(values.begin(), values.end(), TT(0));

    for (auto i = 0u; i < T::dim; i++) {
        a[i] = values[i];
    }

    for (auto i = 0u; i < T::dim; i++) {
        CHECK(values[i] == a[i]);
    }
}

TEST_CASE_TEMPLATE("Vec: initializer_list constructor", T, ARITHMETIC_TYPES) {
    Vec<T, 2> a = {T(0), T(1)};
    CHECK(T(0) == a[0]);
    CHECK(T(1) == a[1]);
}

TEST_CASE_TEMPLATE("Vec: initializer_list constructor", T, ARITHMETIC_TYPES) {
    Vec<T, 3> a = {T(0), T(1), T(2)};
    CHECK(T(0) == a[0]);
    CHECK(T(1) == a[1]);
    CHECK(T(2) == a[2]);
}

TEST_CASE_TEMPLATE("Vec: initializer_list constructor", T, ARITHMETIC_TYPES) {
    Vec<T, 4> a = {T(0), T(1), T(2), T(3)};
    CHECK(T(0) == a[0]);
    CHECK(T(1) == a[1]);
    CHECK(T(2) == a[2]);
    CHECK(T(3) == a[3]);
}

TEST_CASE_TEMPLATE("Vec: Accessors", T, ARITHMETIC_TYPES) {
    Vec<T, 4> a;
    std::iota(a.begin(), a.end(), T(0));

    CHECK(a.r() == a[0]);
    CHECK(a.g() == a[1]);
    CHECK(a.b() == a[2]);
    CHECK(a.a() == a[3]);

    CHECK(a.x() == a[0]);
    CHECK(a.y() == a[1]);
    CHECK(a.z() == a[2]);
}

TEST_CASE_TEMPLATE("Vec: Dot product", T, ARITHMETIC_TYPES_AND_DIMS) {
    Vec<TT, T::dim> a;
    std::iota(a.begin(), a.end(), TT(0));

    Vec<TT, T::dim> b;
    std::iota(b.begin(), b.end(), TT(0));

    auto dot = a.dot(b);
    auto expected = TT(0);
    for (auto i = 0u; i < T::dim; i++) {
        expected += a[i] * b[i];
    }
    CHECK(dot == expected);
}

TEST_CASE_TEMPLATE("Vec: Length squared", T, ARITHMETIC_TYPES_AND_DIMS) {
    Vec<TT, T::dim> a;
    std::iota(a.begin(), a.end(), TT(0));

    auto len_sq = a.length_sq();
    auto expected = TT(0);
    for (auto i = 0u; i < T::dim; i++) {
        expected += a[i] * a[i];
    }
    CHECK(len_sq == expected);
}

TEST_CASE_TEMPLATE("Vec: Length", T, ARITHMETIC_TYPES_AND_DIMS) {
    Vec<TT, T::dim> a;
    std::iota(a.begin(), a.end(), TT(0));

    auto len = a.length();
    auto expected = TT(0);
    for (auto i = 0u; i < T::dim; i++) {
        expected += a[i] * a[i];
    }
    CHECK(doctest::Approx(len) == std::sqrt(expected));
}

TEST_CASE_TEMPLATE("Vec: Normalized", T, ARITHMETIC_TYPES_AND_DIMS) {
    Vec<TT, T::dim> a;
    std::iota(a.begin(), a.end(), TT(0));

    auto norm = a.normalized();
    auto expected = typename Vec<TT, T::dim>::LengthType(0);
    for (auto i = 0u; i < T::dim; i++) {
        expected += a[i] * a[i];
    }
    expected = std::sqrt(expected);
    for (auto i = 0u; i < T::dim; i++) {
        CHECK(doctest::Approx(norm[i]) == a[i] / expected);
    }
}

TEST_CASE_TEMPLATE("Vec: Interpolated", T, ARITHMETIC_TYPES_AND_DIMS) {
    Vec<TT, T::dim> a;
    std::iota(a.begin(), a.end(), TT(0));

    auto interpolated = a.interpolated(TT(2));
    for (auto i = 0u; i < T::dim; i++) {
        CHECK(interpolated[i] == a[i] * TT(2));
    }
}

TEST_CASE_TEMPLATE("Vec: Multiplciation", T, ARITHMETIC_TYPES_AND_DIMS) {
    Vec<TT, T::dim> a;
    std::iota(a.begin(), a.end(), TT(0));

    auto b = a * TT(2);
    for (auto i = 0u; i < T::dim; i++) {
        CHECK(b[i] == a[i] * TT(2));
    }

    auto c = TT(2) * a;
    for (auto i = 0u; i < T::dim; i++) {
        CHECK(c[i] == a[i] * TT(2));
    }
}
