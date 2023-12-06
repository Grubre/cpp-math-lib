#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"
#include "tests_common.hpp"
#include "vector.hpp"

using namespace cml;

TEST_CASE_TEMPLATE("Vec3: test_constructor", T, ARITHMETIC_TYPES) {
    T x = 5;
    T y = 6;
    T z = 7;

    Vec3<T> a(x, y, z);
    CHECK(x == a.x());
    CHECK(y == a.y());
    CHECK(z == a.z());
}

TEST_CASE_TEMPLATE("Vec3: test_copy", T, ARITHMETIC_TYPES) {
    T x = 5;
    T y = 6;
    T z = 7;

    Vec3<T> a(x, y, z);
    Vec3<T> b = a;
    b.x() = 4;
    CHECK(a.x() != b.x());
    CHECK(b.y() == a.y());
    CHECK(b.z() == a.z());
}

TEST_CASE_TEMPLATE("Vec3: test_dot_product", T, ARITHMETIC_TYPES) {
    T a_x = 5;
    T a_y = 6;
    T a_z = 7;

    T b_x = 3;
    T b_y = 3;
    T b_z = 3;

    Vec3<T> a(a_x, a_y, a_z);
    Vec3<T> b(b_x, b_y, b_z);
    CHECK(a_x * b_x + a_y * b_y + a_z * b_z == a.dot(b));
}

TEST_CASE_TEMPLATE("Vec3: test_len_sq", T, ARITHMETIC_TYPES) {
    T x = 5;
    T y = 6;
    T z = 7;

    Vec3<T> a(x, y, z);
    CHECK(x * x + y * y + z * z == a.length_sq());
}

TEST_CASE_TEMPLATE("Vec3: test_len", T, ARITHMETIC_TYPES) {
    T x = 5;
    T y = 6;
    T z = 7;

    Vec3<T> a(x, y, z);
    CHECK(doctest::Approx(std::sqrt(x * x + y * y + z * z)) == a.length());
}

TEST_CASE_TEMPLATE("Vec3: test_norm", T, ARITHMETIC_TYPES) {
    T x = 5;
    T y = 6;
    T z = 7;

    Vec3<T> a(x, y, z);
    auto norm = a.normalized();
    CHECK(doctest::Approx(1.0f) == norm.length());
}

TEST_CASE_TEMPLATE("Vec3: unary_minus_operator", T, ARITHMETIC_TYPES) {
    T x = 5;
    T y = 6;
    T z = 7;

    Vec3<T> a(x, y, z);
    auto b = -a;

    CHECK(-x == b.x());
    CHECK(-y == b.y());
    CHECK(-z == b.z());
}

TEST_CASE_TEMPLATE("Vec3: plus_operator", T, ARITHMETIC_TYPES) {
    T a_x = 5;
    T a_y = 6;
    T a_z = 7;
    T b_x = 8;
    T b_y = 9;
    T b_z = 10;

    Vec3<T> a(a_x, a_y, a_z);
    Vec3<T> b(b_x, b_y, b_z);
    auto c = a + b;

    CHECK(a_x + b_x == c.x());
    CHECK(a_y + b_y == c.y());
    CHECK(a_z + b_z == c.z());
}

TEST_CASE_TEMPLATE("Vec3: minus_operator", T, ARITHMETIC_TYPES) {
    T a_x = 5;
    T a_y = 6;
    T a_z = 7;
    T b_x = 8;
    T b_y = 9;
    T b_z = 10;

    Vec3<T> a(a_x, a_y, a_z);
    Vec3<T> b(b_x, b_y, b_z);
    auto c = a - b;

    CHECK(a_x - b_x == c.x());
    CHECK(a_y - b_y == c.y());
    CHECK(a_z - b_z == c.z());
}

TEST_CASE_TEMPLATE("Vec3: equals_operator", T, ARITHMETIC_TYPES) {
    T a_x = 5;
    T a_y = 6;
    T a_z = 7;
    T b_x = 8;
    T b_y = 9;
    T b_z = 10;

    Vec3<T> a(a_x, a_y, a_z);
    Vec3<T> b(b_x, b_y, b_z);

    CHECK(a == a);
    CHECK(a != b);
}

TEST_CASE_TEMPLATE("Vec3: pluseq_operator", T, ARITHMETIC_TYPES) {
    T a_x = 5;
    T a_y = 6;
    T a_z = 7;
    T b_x = 8;
    T b_y = 9;
    T b_z = 10;

    Vec3<T> a(a_x, a_y, a_z);
    Vec3<T> b(b_x, b_y, b_z);

    a += b;

    CHECK(a.x() == a_x + b_x);
    CHECK(a.y() == a_y + b_y);
    CHECK(a.z() == a_z + b_z);
}

TEST_CASE_TEMPLATE("Vec3: minuseq_operator", T, ARITHMETIC_TYPES) {
    T a_x = 5;
    T a_y = 6;
    T a_z = 7;
    T b_x = 8;
    T b_y = 9;
    T b_z = 10;

    Vec3<T> a(a_x, a_y, a_z);
    Vec3<T> b(b_x, b_y, b_z);

    a -= b;

    CHECK(a.x() == a_x - b_x);
    CHECK(a.y() == a_y - b_y);
    CHECK(a.z() == a_z - b_z);
}

TEST_CASE_TEMPLATE("Vec3: mult_by_scalar_operator", T, ARITHMETIC_TYPES) {
    T a_x = 5;
    T a_y = 6;
    T a_z = 7;
    const T c = 3;

    Vec3<T> a(a_x, a_y, a_z);
    auto b = a * c;

    CHECK(b.x() == a_x * c);
    CHECK(b.y() == a_y * c);
    CHECK(b.z() == a_z * c);
}

TEST_CASE_TEMPLATE("Vec3: div_by_scalar_operator", T, ARITHMETIC_TYPES) {
    T a_x = 5;
    T a_y = 6;
    T a_z = 7;
    const T c = 3;

    Vec3<T> a(a_x, a_y, a_z);
    auto b = a / c;

    CHECK(b.x() == a_x / c);
    CHECK(b.y() == a_y / c);
    CHECK(b.z() == a_z / c);
}

TEST_CASE_TEMPLATE("Vec3: multeq_by_scalar_operator", T, ARITHMETIC_TYPES) {
    T a_x = 5;
    T a_y = 6;
    T a_z = 7;
    const T c = 3;

    Vec3<T> a(a_x, a_y, a_z);
    a *= c;

    CHECK(a.x() == a_x * c);
    CHECK(a.y() == a_y * c);
    CHECK(a.z() == a_z * c);
}

TEST_CASE_TEMPLATE("Vec3: diveq_by_scalar_operator", T, ARITHMETIC_TYPES) {
    T a_x = 5;
    T a_y = 6;
    T a_z = 7;
    const T c = 3;

    Vec3<T> a(a_x, a_y, a_z);
    a /= c;

    CHECK(a.x() == a_x / c);
    CHECK(a.y() == a_y / c);
    CHECK(a.z() == a_z / c);
}
