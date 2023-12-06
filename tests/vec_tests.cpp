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
