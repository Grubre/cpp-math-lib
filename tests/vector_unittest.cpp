#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"
#include "vector.hpp"
TEST_CASE("Vec2: test_constructor") {
    int x = 5;
    int y = 6;

    Vec2i a(x, y);
    CHECK(x == a.x);
    CHECK(y == a.y);
}

TEST_CASE("Vec2: test_copy") {
    int x = 5;
    int y = 6;

    Vec2i a(x, y);
    Vec2i b = a;
    b.x = 4;
    CHECK(a.x != b.x);
    CHECK(b.y == a.y);
}

TEST_CASE("Vec2: test_dot_product") {
    int a_x = 5;
    int a_y = 6;

    int b_x = 2;
    int b_y = 3;

    Vec2i a(a_x, a_y);
    Vec2i b(b_x, b_y);
    CHECK(a_x * b_x + a_y * b_y == a.dot(b));
}
TEST_CASE("Vec2: test_len_sq") {
    int x = 5;
    int y = 6;

    Vec2i a(x,y);
    CHECK(x * x + y * y == a.length_sq());
}
TEST_CASE("Vec2: test_len") {
    int x = 5;
    int y = 6;

    Vec2i a(x,y);
    CHECK(doctest::Approx(std::sqrt(x * x + y * y)) == a.length());
}

TEST_CASE("Vec2: test_norm") {
    int x = 5;
    int y = 6;

    Vec2i a(x,y);
    auto norm = a.normalized();
    CHECK(doctest::Approx(1.0f) == norm.length());
}

TEST_CASE("Vec2: test_perp") {
    int x = 5;
    int y = 6;

    Vec2i a(x,y);
    auto perp = a.perpendicular();
    CHECK(0 == a.dot(perp));
    CHECK(-y == perp.x);
    CHECK(x == perp.y);
}

TEST_CASE("Vec2: unary_minus_operator") {
    int x = 5;
    int y = 6;

    Vec2i a(x,y);
    auto b = -a;

    CHECK(-x == b.x);
    CHECK(-y == b.y);
}

TEST_CASE("Vec2: plus_operator") {
    int a_x = 5;
    int a_y = 6;
    int b_x = 7;
    int b_y = 8;

    Vec2i a(a_x, a_y);
    Vec2i b(b_x, b_y);
    auto c = a + b;

    CHECK(a_x + b_x == c.x);
    CHECK(a_y + b_y == c.y);
}

TEST_CASE("Vec2: minus_operator") {
    int a_x = 5;
    int a_y = 6;
    int b_x = 7;
    int b_y = 8;

    Vec2i a(a_x, a_y);
    Vec2i b(b_x, b_y);
    auto c = a - b;

    CHECK(a_x - b_x == c.x);
    CHECK(a_y - b_y == c.y);
}

TEST_CASE("Vec2: equals_operator") {
    int a_x = 5;
    int a_y = 6;
    int b_x = 7;
    int b_y = 8;

    Vec2i a(a_x, a_y);
    Vec2i b(b_x, b_y);

    CHECK(a == a);
    CHECK(a != b);
}

TEST_CASE("Vec2: pluseq_operator") {
    int a_x = 5;
    int a_y = 6;
    int b_x = 7;
    int b_y = 8;

    Vec2i a(a_x, a_y);
    Vec2i b(b_x, b_y);
    a += b;

    CHECK(a.x == a_x + b_x);
    CHECK(a.y == a_y + b_y);
}

TEST_CASE("Vec2: minuseq_operator") {
    int a_x = 5;
    int a_y = 6;
    int b_x = 7;
    int b_y = 8;

    Vec2i a(a_x, a_y);
    Vec2i b(b_x, b_y);
    a -= b;

    CHECK(a.x == a_x - b_x);
    CHECK(a.y == a_y - b_y);
}

TEST_CASE("Vec2: mult_by_scalar_operator") {
    int a_x = 5;
    int a_y = 6;
    const int c = 2;

    Vec2i a(a_x, a_y);
    auto b = a * c;

    CHECK(b.x == a_x * c);
    CHECK(b.y == a_y * c);
}

TEST_CASE("Vec2: div_by_scalar_operator") {
    int a_x = 5;
    int a_y = 6;
    const int c = 2;

    Vec2i a(a_x, a_y);
    auto b = a / c;

    CHECK(b.x == a_x / c);
    CHECK(b.y == a_y / c);
}

TEST_CASE("Vec2: multeq_by_scalar_operator") {
    int a_x = 5;
    int a_y = 6;
    const int c = 2;

    Vec2i a(a_x, a_y);
    a *= c;

    CHECK(a.x == a_x * c);
    CHECK(a.y == a_y * c);
}

TEST_CASE("Vec2: diveq_by_scalar_operator") {
    int a_x = 5;
    int a_y = 6;
    const int c = 2;

    Vec2i a(a_x, a_y);
    a /= c;

    CHECK(a.x == a_x / c);
    CHECK(a.y == a_y / c);
}


TEST_CASE("Vec3: test_constructor") {
    int x = 5;
    int y = 6;
    int z = 7;

    Vec3i a(x,y,z);
    CHECK(x == a.x);
    CHECK(y == a.y);
    CHECK(z == a.z);
}

TEST_CASE("Vec3: test_copy") {
    int x = 5;
    int y = 6;
    int z = 7;

    Vec3i a(x,y,z);
    Vec3i b = a;
    b.x = 4;
    CHECK(a.x != b.x);
    CHECK(b.y == a.y);
    CHECK(b.z == a.z);
}

TEST_CASE("Vec3: test_dot_product") {
    int a_x = 5;
    int a_y = 6;
    int a_z = 7;

    int b_x = 3;
    int b_y = 3;
    int b_z = 3;


    Vec3i a(a_x, a_y, a_z);
    Vec3i b(b_x, b_y, b_z);
    CHECK(a_x * b_x + a_y * b_y + a_z * b_z == a.dot(b));
}

TEST_CASE("Vec3: test_len_sq") {
    int x = 5;
    int y = 6;
    int z = 7;

    Vec3i a(x,y,z);
    CHECK(x * x + y * y + z * z == a.length_sq());
}

TEST_CASE("Vec3: test_len") {
    int x = 5;
    int y = 6;
    int z = 7;

    Vec3i a(x,y,z);
    CHECK(doctest::Approx(std::sqrt(x * x + y * y + z * z)) == a.length());
}

TEST_CASE("Vec3: test_norm") {
    int x = 5;
    int y = 6;
    int z = 7;

    Vec3i a(x,y,z);
    auto norm = a.normalized();
    CHECK(doctest::Approx(1.0f) == norm.length());
}

TEST_CASE("Vec3: unary_minus_operator") {
    int x = 5;
    int y = 6;
    int z = 7;

    Vec3i a(x,y,z);
    auto b = -a;

    CHECK(-x == b.x);
    CHECK(-y == b.y);
    CHECK(-z == b.z);
}

TEST_CASE("Vec3: plus_operator") {
    int a_x = 5;
    int a_y = 6;
    int a_z = 7;
    int b_x = 8;
    int b_y = 9;
    int b_z = 10;


    Vec3i a(a_x, a_y, a_z);
    Vec3i b(b_x, b_y, b_z);
    auto c = a + b;

    CHECK(a_x + b_x == c.x);
    CHECK(a_y + b_y == c.y);
    CHECK(a_z + b_z == c.z);
}

TEST_CASE("Vec3: minus_operator") {
    int a_x = 5;
    int a_y = 6;
    int a_z = 7;
    int b_x = 8;
    int b_y = 9;
    int b_z = 10;


    Vec3i a(a_x, a_y, a_z);
    Vec3i b(b_x, b_y, b_z);
    auto c = a - b;

    CHECK(a_x - b_x == c.x);
    CHECK(a_y - b_y == c.y);
    CHECK(a_z - b_z == c.z);
}

TEST_CASE("Vec3: equals_operator") {
    int a_x = 5;
    int a_y = 6;
    int a_z = 7;
    int b_x = 8;
    int b_y = 9;
    int b_z = 10;

    Vec3i a(a_x, a_y, a_z);
    Vec3i b(b_x, b_y, b_z);

    CHECK(a == a);
    CHECK(a != b);
}

TEST_CASE("Vec3: pluseq_operator") {
    int a_x = 5;
    int a_y = 6;
    int a_z = 7;
    int b_x = 8;
    int b_y = 9;
    int b_z = 10;

    Vec3i a(a_x, a_y, a_z);
    Vec3i b(b_x, b_y, b_z);

    a += b;

    CHECK(a.x == a_x + b_x);
    CHECK(a.y == a_y + b_y);
    CHECK(a.z == a_z + b_z);
}

TEST_CASE("Vec3: minuseq_operator") {
    int a_x = 5;
    int a_y = 6;
    int a_z = 7;
    int b_x = 8;
    int b_y = 9;
    int b_z = 10;

    Vec3i a(a_x, a_y, a_z);
    Vec3i b(b_x, b_y, b_z);

    a -= b;

    CHECK(a.x == a_x - b_x);
    CHECK(a.y == a_y - b_y);
    CHECK(a.z == a_z - b_z);
}

TEST_CASE("Vec3: mult_by_scalar_operator") {
    int a_x = 5;
    int a_y = 6;
    int a_z = 7;
    const int c = 3;

    Vec3i a(a_x, a_y, a_z);
    auto b = a * c;

    CHECK(b.x == a_x * c);
    CHECK(b.y == a_y * c);
    CHECK(b.z == a_z * c);
}

TEST_CASE("Vec3: div_by_scalar_operator") {
    int a_x = 5;
    int a_y = 6;
    int a_z = 7;
    const int c = 3;

    Vec3i a(a_x, a_y, a_z);
    auto b = a / c;

    CHECK(b.x == a_x / c);
    CHECK(b.y == a_y / c);
    CHECK(b.z == a_z / c);
}

TEST_CASE("Vec3: multeq_by_scalar_operator") {
    int a_x = 5;
    int a_y = 6;
    int a_z = 7;
    const int c = 3;

    Vec3i a(a_x, a_y, a_z);
    a *= c;

    CHECK(a.x == a_x * c);
    CHECK(a.y == a_y * c);
    CHECK(a.z == a_z * c);
}

TEST_CASE("Vec3: diveq_by_scalar_operator") {
    int a_x = 5;
    int a_y = 6;
    int a_z = 7;
    const int c = 3;

    Vec3i a(a_x, a_y, a_z);
    a /= c;

    CHECK(a.x == a_x / c);
    CHECK(a.y == a_y / c);
    CHECK(a.z == a_z / c);
}
