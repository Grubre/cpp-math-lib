#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"
#include "vector.hpp"
#include "tests_common.hpp"

using namespace cml;

TEST_CASE_TEMPLATE("Vec2: test_constructor", T, ARITHMETIC_TYPES) {
    T x = 5;
    T y = 6;

    Vec2<T> a{x, y};
    CHECK(x == a.x);
    CHECK(y == a.y);
}

TEST_CASE_TEMPLATE("Vec2: test_copy", T, ARITHMETIC_TYPES) {
    T x = 5;
    T y = 6;

    Vec2<T> a{x, y};
    Vec2<T> b = a;
    b.x = 4;
    CHECK(a.x != b.x);
    CHECK(b.y == a.y);
}

TEST_CASE_TEMPLATE("Vec2: test_dot_product", T, ARITHMETIC_TYPES) {
    T a_x = 5;
    T a_y = 6;

    T b_x = 2;
    T b_y = 3;

    Vec2<T> a(a_x, a_y);
    Vec2<T> b(b_x, b_y);
    CHECK(a_x * b_x + a_y * b_y == a.dot(b));
}

TEST_CASE_TEMPLATE("Vec2: test_len_sq", T, ARITHMETIC_TYPES) {
    T x = 5;
    T y = 6;

    Vec2<T> a(x, y);
    CHECK(x * x + y * y == a.length_sq());
}

TEST_CASE_TEMPLATE("Vec2: test_len", T, ARITHMETIC_TYPES) {
    T x = 5;
    T y = 6;

    Vec2<T> a(x, y);
    CHECK(doctest::Approx(std::sqrt(x * x + y * y)) == a.length());
}

TEST_CASE_TEMPLATE("Vec2: test_norm", T, ARITHMETIC_TYPES) {
    T x = 5;
    T y = 6;

    Vec2<T> a(x, y);
    auto norm = a.normalized();
    CHECK(doctest::Approx(1.0f) == norm.length());
}

TEST_CASE_TEMPLATE("Vec2: test_perp", T, ARITHMETIC_TYPES) {
    T x = 5;
    T y = 6;

    Vec2<T> a(x, y);
    auto perp = a.perpendicular();
    CHECK(0 == a.dot(perp));
    CHECK(-y == perp.x);
    CHECK(x == perp.y);
}

TEST_CASE_TEMPLATE("Vec2: unary_minus_operator", T, ARITHMETIC_TYPES) {
    T x = 5;
    T y = 6;

    Vec2<T> a(x, y);
    auto b = -a;

    CHECK(-x == b.x);
    CHECK(-y == b.y);
}

TEST_CASE_TEMPLATE("Vec2: plus_operator", T, ARITHMETIC_TYPES) {
    T a_x = 5;
    T a_y = 6;
    T b_x = 7;
    T b_y = 8;

    Vec2<T> a(a_x, a_y);
    Vec2<T> b(b_x, b_y);
    auto c = a + b;

    CHECK(a_x + b_x == c.x);
    CHECK(a_y + b_y == c.y);
}

TEST_CASE_TEMPLATE("Vec2: minus_operator", T, ARITHMETIC_TYPES) {
    T a_x = 5;
    T a_y = 6;
    T b_x = 7;
    T b_y = 8;

    Vec2<T> a(a_x, a_y);
    Vec2<T> b(b_x, b_y);
    auto c = a - b;

    CHECK(a_x - b_x == c.x);
    CHECK(a_y - b_y == c.y);
}

TEST_CASE_TEMPLATE("Vec2: equals_operator", T, ARITHMETIC_TYPES) {
    T a_x = 5;
    T a_y = 6;
    T b_x = 7;
    T b_y = 8;

    Vec2<T> a(a_x, a_y);
    Vec2<T> b(b_x, b_y);

    CHECK(a == a);
    CHECK(a != b);
}

TEST_CASE_TEMPLATE("Vec2: pluseq_operator", T, ARITHMETIC_TYPES) {
    T a_x = 5;
    T a_y = 6;
    T b_x = 7;
    T b_y = 8;

    Vec2<T> a(a_x, a_y);
    Vec2<T> b(b_x, b_y);
    a += b;

    CHECK(a.x == a_x + b_x);
    CHECK(a.y == a_y + b_y);
}

TEST_CASE_TEMPLATE("Vec2: minuseq_operator", T, ARITHMETIC_TYPES) {
    T a_x = 5;
    T a_y = 6;
    T b_x = 7;
    T b_y = 8;

    Vec2<T> a(a_x, a_y);
    Vec2<T> b(b_x, b_y);
    a -= b;

    CHECK(a.x == a_x - b_x);
    CHECK(a.y == a_y - b_y);
}

TEST_CASE_TEMPLATE("Vec2: mult_by_scalar_operator", T, ARITHMETIC_TYPES) {
    T a_x = 5;
    T a_y = 6;
    const T c = 2;

    Vec2<T> a(a_x, a_y);
    auto b = a * c;

    CHECK(b.x == a_x * c);
    CHECK(b.y == a_y * c);
}

TEST_CASE_TEMPLATE("Vec2: div_by_scalar_operator", T, ARITHMETIC_TYPES) {
    T a_x = 5;
    T a_y = 6;
    const T c = 2;

    Vec2<T> a(a_x, a_y);
    auto b = a / c;

    CHECK(b.x == a_x / c);
    CHECK(b.y == a_y / c);
}

TEST_CASE_TEMPLATE("Vec2: multeq_by_scalar_operator", T, ARITHMETIC_TYPES) {
    T a_x = 5;
    T a_y = 6;
    const T c = 2;

    Vec2<T> a(a_x, a_y);
    a *= c;

    CHECK(a.x == a_x * c);
    CHECK(a.y == a_y * c);
}

TEST_CASE_TEMPLATE("Vec2: diveq_by_scalar_operator", T, ARITHMETIC_TYPES) {
    T a_x = 5;
    T a_y = 6;
    const T c = 2;

    Vec2<T> a(a_x, a_y);
    a /= c;

    CHECK(a.x == a_x / c);
    CHECK(a.y == a_y / c);
}
