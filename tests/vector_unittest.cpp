#include <gtest/gtest.h>
#include "vector.hpp"

TEST(Vec2, test_constructor) {
    int x = 5;
    int y = 6;

    Vec2i a(x,y);
    EXPECT_EQ(x, a.x);
    EXPECT_EQ(y, a.y);
}

TEST(Vec2, test_copy) {
    int x = 5;
    int y = 6;

    Vec2i a(x,y);
    Vec2i b = a;
    b.x = 4;
    EXPECT_NE(a.x, b.x);
    EXPECT_EQ(b.y, a.y);
}

TEST(Vec2, test_dot_product) {
    int a_x = 5;
    int a_y = 6;

    int b_x = 2;
    int b_y = 3;


    Vec2i a(a_x, a_y);
    Vec2i b(b_x, b_y);
    EXPECT_EQ(a_x * b_x + a_y * b_y, a.dot(b));
}

TEST(Vec2, test_len_sq) {
    int x = 5;
    int y = 6;

    Vec2i a(x,y);
    EXPECT_EQ(x * x + y * y, a.length_sq());
}

TEST(Vec2, test_len) {
    int x = 5;
    int y = 6;

    Vec2i a(x,y);
    EXPECT_FLOAT_EQ(std::sqrt(x * x + y * y), a.length());
}

TEST(Vec2, test_norm) {
    int x = 5;
    int y = 6;

    Vec2i a(x,y);
    auto norm = a.normalized();
    EXPECT_FLOAT_EQ(1.0f, norm.length());
}

TEST(Vec2, test_perp) {
    int x = 5;
    int y = 6;

    Vec2i a(x,y);
    auto perp = a.perpendicular();
    EXPECT_EQ(0, a.dot(perp));
    EXPECT_EQ(-y, perp.x);
    EXPECT_EQ(x, perp.y);
}

TEST(Vec2operators, unary_minus_operator) {
    int x = 5;
    int y = 6;

    Vec2i a(x,y);
    auto b = -a;

    EXPECT_EQ(-x, b.x);
    EXPECT_EQ(-y, b.y);
}

TEST(Vec2operators, plus_operator) {
    int a_x = 5;
    int a_y = 6;
    int b_x = 7;
    int b_y = 8;

    Vec2i a(a_x, a_y);
    Vec2i b(b_x, b_y);
    auto c = a + b;

    EXPECT_EQ(a_x + b_x, c.x);
    EXPECT_EQ(a_y + b_y, c.y);
}

TEST(Vec2operators, minus_operator) {
    int a_x = 5;
    int a_y = 6;
    int b_x = 7;
    int b_y = 8;

    Vec2i a(a_x, a_y);
    Vec2i b(b_x, b_y);
    auto c = a - b;

    EXPECT_EQ(a_x - b_x, c.x);
    EXPECT_EQ(a_y - b_y, c.y);
}

TEST(Vec2operators, equals_operator) {
    int a_x = 5;
    int a_y = 6;
    int b_x = 7;
    int b_y = 8;

    Vec2i a(a_x, a_y);
    Vec2i b(b_x, b_y);

    EXPECT_EQ(a, a);
    EXPECT_NE(a, b);
}

TEST(Vec2operators, pluseq_operator) {
    int a_x = 5;
    int a_y = 6;
    int b_x = 7;
    int b_y = 8;

    Vec2i a(a_x, a_y);
    Vec2i b(b_x, b_y);
    a += b;

    EXPECT_EQ(a.x, a_x + b_x);
    EXPECT_EQ(a.y, a_y + b_y);
}

TEST(Vec2operators, minuseq_operator) {
    int a_x = 5;
    int a_y = 6;
    int b_x = 7;
    int b_y = 8;

    Vec2i a(a_x, a_y);
    Vec2i b(b_x, b_y);
    a -= b;

    EXPECT_EQ(a.x, a_x - b_x);
    EXPECT_EQ(a.y, a_y - b_y);
}

TEST(Vec2operators, mult_by_scalar_operator) {
    int a_x = 5;
    int a_y = 6;
    const int c = 2;

    Vec2i a(a_x, a_y);
    auto b = a * c;

    EXPECT_EQ(b.x, a_x * c);
    EXPECT_EQ(b.y, a_y * c);
}

TEST(Vec2operators, div_by_scalar_operator) {
    int a_x = 5;
    int a_y = 6;
    const int c = 2;

    Vec2i a(a_x, a_y);
    auto b = a / c;

    EXPECT_EQ(b.x, a_x / c);
    EXPECT_EQ(b.y, a_y / c);
}

TEST(Vec2operators, multeq_by_scalar_operator) {
    int a_x = 5;
    int a_y = 6;
    const int c = 2;

    Vec2i a(a_x, a_y);
    a *= c;

    EXPECT_EQ(a.x, a_x * c);
    EXPECT_EQ(a.y, a_y * c);
}

TEST(Vec2operators, diveq_by_scalar_operator) {
    int a_x = 5;
    int a_y = 6;
    const int c = 2;

    Vec2i a(a_x, a_y);
    a /= c;

    EXPECT_EQ(a.x, a_x / c);
    EXPECT_EQ(a.y, a_y / c);
}


TEST(Vec3, test_constructor) {
    int x = 5;
    int y = 6;
    int z = 7;

    Vec3i a(x,y,z);
    EXPECT_EQ(x, a.x);
    EXPECT_EQ(y, a.y);
    EXPECT_EQ(z, a.z);
}

TEST(Vec3, test_copy) {
    int x = 5;
    int y = 6;
    int z = 7;

    Vec3i a(x,y,z);
    Vec3i b = a;
    b.x = 4;
    EXPECT_NE(a.x, b.x);
    EXPECT_EQ(b.y, a.y);
    EXPECT_EQ(b.z, a.z);
}

TEST(Vec3, test_dot_product) {
    int a_x = 5;
    int a_y = 6;
    int a_z = 7;

    int b_x = 3;
    int b_y = 3;
    int b_z = 3;


    Vec3i a(a_x, a_y, a_z);
    Vec3i b(b_x, b_y, b_z);
    EXPECT_EQ(a_x * b_x + a_y * b_y + a_z * b_z, a.dot(b));
}

TEST(Vec3, test_len_sq) {
    int x = 5;
    int y = 6;
    int z = 7;

    Vec3i a(x,y,z);
    EXPECT_EQ(x * x + y * y + z * z, a.length_sq());
}

TEST(Vec3, test_len) {
    int x = 5;
    int y = 6;
    int z = 7;

    Vec3i a(x,y,z);
    EXPECT_FLOAT_EQ(std::sqrt(x * x + y * y + z * z), a.length());
}

TEST(Vec3, test_norm) {
    int x = 5;
    int y = 6;
    int z = 7;

    Vec3i a(x,y,z);
    auto norm = a.normalized();
    EXPECT_FLOAT_EQ(1.0f, norm.length());
}

TEST(Vec3operators, unary_minus_operator) {
    int x = 5;
    int y = 6;
    int z = 7;

    Vec3i a(x,y,z);
    auto b = -a;

    EXPECT_EQ(-x, b.x);
    EXPECT_EQ(-y, b.y);
    EXPECT_EQ(-z, b.z);
}

TEST(Vec3operators, plus_operator) {
    int a_x = 5;
    int a_y = 6;
    int a_z = 7;
    int b_x = 8;
    int b_y = 9;
    int b_z = 10;


    Vec3i a(a_x, a_y, a_z);
    Vec3i b(b_x, b_y, b_z);
    auto c = a + b;

    EXPECT_EQ(a_x + b_x, c.x);
    EXPECT_EQ(a_y + b_y, c.y);
    EXPECT_EQ(a_z + b_z, c.z);
}

TEST(Vec3operators, minus_operator) {
    int a_x = 5;
    int a_y = 6;
    int a_z = 7;
    int b_x = 8;
    int b_y = 9;
    int b_z = 10;


    Vec3i a(a_x, a_y, a_z);
    Vec3i b(b_x, b_y, b_z);
    auto c = a - b;

    EXPECT_EQ(a_x - b_x, c.x);
    EXPECT_EQ(a_y - b_y, c.y);
    EXPECT_EQ(a_z - b_z, c.z);
}

TEST(Vec3operators, equals_operator) {
    int a_x = 5;
    int a_y = 6;
    int a_z = 7;
    int b_x = 8;
    int b_y = 9;
    int b_z = 10;

    Vec3i a(a_x, a_y, a_z);
    Vec3i b(b_x, b_y, b_z);

    EXPECT_EQ(a, a);
    EXPECT_NE(a, b);
}

TEST(Vec3operators, pluseq_operator) {
    int a_x = 5;
    int a_y = 6;
    int a_z = 7;
    int b_x = 8;
    int b_y = 9;
    int b_z = 10;

    Vec3i a(a_x, a_y, a_z);
    Vec3i b(b_x, b_y, b_z);

    a += b;

    EXPECT_EQ(a.x, a_x + b_x);
    EXPECT_EQ(a.y, a_y + b_y);
    EXPECT_EQ(a.z, a_z + b_z);
}

TEST(Vec3operators, minuseq_operator) {
    int a_x = 5;
    int a_y = 6;
    int a_z = 7;
    int b_x = 8;
    int b_y = 9;
    int b_z = 10;

    Vec3i a(a_x, a_y, a_z);
    Vec3i b(b_x, b_y, b_z);

    a -= b;

    EXPECT_EQ(a.x, a_x - b_x);
    EXPECT_EQ(a.y, a_y - b_y);
    EXPECT_EQ(a.z, a_z - b_z);
}

TEST(Vec3operators, mult_by_scalar_operator) {
    int a_x = 5;
    int a_y = 6;
    int a_z = 7;
    const int c = 3;

    Vec3i a(a_x, a_y, a_z);
    auto b = a * c;

    EXPECT_EQ(b.x, a_x * c);
    EXPECT_EQ(b.y, a_y * c);
    EXPECT_EQ(b.z, a_z * c);
}

TEST(Vec3operators, div_by_scalar_operator) {
    int a_x = 5;
    int a_y = 6;
    int a_z = 7;
    const int c = 3;

    Vec3i a(a_x, a_y, a_z);
    auto b = a / c;

    EXPECT_EQ(b.x, a_x / c);
    EXPECT_EQ(b.y, a_y / c);
    EXPECT_EQ(b.z, a_z / c);
}

TEST(Vec3operators, multeq_by_scalar_operator) {
    int a_x = 5;
    int a_y = 6;
    int a_z = 7;
    const int c = 3;

    Vec3i a(a_x, a_y, a_z);
    a *= c;

    EXPECT_EQ(a.x, a_x * c);
    EXPECT_EQ(a.y, a_y * c);
    EXPECT_EQ(a.z, a_z * c);
}

TEST(Vec3operators, diveq_by_scalar_operator) {
    int a_x = 5;
    int a_y = 6;
    int a_z = 7;
    const int c = 3;

    Vec3i a(a_x, a_y, a_z);
    a /= c;

    EXPECT_EQ(a.x, a_x / c);
    EXPECT_EQ(a.y, a_y / c);
    EXPECT_EQ(a.z, a_z / c);
}
