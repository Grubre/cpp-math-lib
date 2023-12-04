#pragma once
#include "common.hpp"
#include "matrix.hpp"
#include <cmath>
#include <ostream>

template <arithmetic T> class Vec2;
template <arithmetic T> class Vec3;

template <arithmetic T> class Vec3 {
  public:
    T x;
    T y;
    T z;

    constexpr Vec3() : x(0), y(0), z(0) {}
    explicit Vec3(Vec2<T> vec) : x(vec.x), y(vec.y), z(0) {}
    constexpr Vec3(T x, T y, T z) : x(x), y(y), z(z) {}

    constexpr T dot(const Vec3<T> &rhs) const {
        return x * rhs.x + y * rhs.y + z * rhs.z;
    }

    constexpr T length_sq() const { return x * x + y * y + z * z; }

    constexpr float length() const { return std::sqrt(length_sq()); }

    constexpr Vec3<float> normalized() const {
        float len = length();
        return Vec3<float>(x / len, y / len, z / len);
    }

    constexpr Vec3<float> interpolate(float scalar) const {
        return (*this) * scalar;
    }
};

using Vec3i = Vec3<int>;
using Vec3u = Vec3<unsigned int>;
using Vec3d = Vec3<double>;
using Vec3f = Vec3<float>;

template <arithmetic T> class Vec2 {
  public:
    T x;
    T y;

    constexpr Vec2() : x(0), y(0) {}
    explicit Vec2(Vec3<T> vec) : x(vec.x), y(vec.y) {}
    constexpr Vec2(T x, T y) : x(x), y(y) {}

    constexpr T dot(const Vec2<T> &rhs) const { return x * rhs.x + y * rhs.y; }

    constexpr T length_sq() const { return x * x + y * y; }

    constexpr float length() const { return std::sqrt(length_sq()); }

    constexpr Vec2<float> normalized() const {
        float len = length();
        return Vec2<float>(x / len, y / len);
    }

    constexpr Vec2<T> perpendicular() const { return {-y, x}; }

    constexpr Vec2<float> interpolate(float scalar) const {
        return (*this) * scalar;
    }
};

using Vec2i = Vec2<int>;
using Vec2u = Vec2<unsigned int>;
using Vec2d = Vec2<double>;
using Vec2f = Vec2<float>;

template <arithmetic T> Vec2<T> operator-(const Vec2<T> &rhs) {
    return Vec2(-rhs.x, -rhs.y);
}

template <arithmetic T>
Vec2<T> operator+(const Vec2<T> &lhs, const Vec2<T> &rhs) {
    return Vec2(lhs.x + rhs.x, lhs.y + rhs.y);
}

template <arithmetic T> Vec2<T> &operator+=(Vec2<T> &lhs, const Vec2<T> &rhs) {
    lhs.x += rhs.x;
    lhs.y += rhs.y;
    return lhs;
}

template <arithmetic T>
Vec2<T> operator-(const Vec2<T> &lhs, const Vec2<T> &rhs) {
    return Vec2(lhs.x - rhs.x, lhs.y - rhs.y);
}

template <arithmetic T> Vec2<T> &operator-=(Vec2<T> &lhs, const Vec2<T> &rhs) {
    lhs.x -= rhs.x;
    lhs.y -= rhs.y;
    return lhs;
}

template <arithmetic T> Vec2<T> operator*(T lhs, const Vec2<T> &rhs) {
    return Vec2(lhs * rhs.x, lhs * rhs.y);
}

template <arithmetic T> Vec2<T> operator*(const Vec2<T> &lhs, T rhs) {
    return Vec2(lhs.x * rhs, lhs.y * rhs);
}

template <arithmetic T> Vec2<T> &operator*=(Vec2<T> &lhs, const T rhs) {
    lhs.x *= rhs;
    lhs.y *= rhs;
    return lhs;
}

// divide by a scalar
template <arithmetic T> Vec2<T> operator/(const Vec2<T> &lhs, T rhs) {
    return Vec2(lhs.x / rhs, lhs.y / rhs);
}

template <arithmetic T> Vec2<T> &operator/=(Vec2<T> &lhs, const T rhs) {
    lhs.x /= rhs;
    lhs.y /= rhs;
    return lhs;
}

template <arithmetic T>
bool operator==(const Vec2<T> &lhs, const Vec2<T> &rhs) {
    return rhs.x == lhs.x && rhs.y == lhs.y;
}

template <arithmetic T>
std::ostream &operator<<(std::ostream &out, const Vec2<T> &vec) {
    return out << vec.x << " " << vec.y;
}

template <arithmetic T> Vec3<T> operator-(const Vec3<T> &rhs) {
    return Vec3(-rhs.x, -rhs.y, -rhs.z);
}

template <arithmetic T>
Vec3<T> operator+(const Vec3<T> &lhs, const Vec3<T> &rhs) {
    return Vec3(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
}

template <arithmetic T> Vec3<T> &operator+=(Vec3<T> &lhs, const Vec3<T> &rhs) {
    lhs.x += rhs.x;
    lhs.y += rhs.y;
    lhs.z += rhs.z;
    return lhs;
}

// odejmowanie
template <arithmetic T>
Vec3<T> operator-(const Vec3<T> &lhs, const Vec3<T> &rhs) {
    return Vec3(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
}

template <arithmetic T> Vec3<T> &operator-=(Vec3<T> &lhs, const Vec3<T> &rhs) {
    lhs.x -= rhs.x;
    lhs.y -= rhs.y;
    lhs.z -= rhs.z;
    return lhs;
}

template <arithmetic T> Vec3<T> operator*(T lhs, const Vec3<T> &rhs) {
    return Vec3(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z);
}

template <arithmetic T> Vec3<T> operator*(const Vec3<T> &lhs, T rhs) {
    return Vec3(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs);
}

template <arithmetic T> Vec3<T> &operator*=(Vec3<T> &lhs, const T rhs) {
    lhs.x *= rhs;
    lhs.y *= rhs;
    lhs.z *= rhs;
    return lhs;
}

template <arithmetic T> Vec3<T> operator/(const Vec3<T> &lhs, T rhs) {
    return Vec3(lhs.x / rhs, lhs.y / rhs, lhs.z / rhs);
}

template <arithmetic T> Vec3<T> &operator/=(Vec3<T> &lhs, const T rhs) {
    lhs.x /= rhs;
    lhs.y /= rhs;
    lhs.z /= rhs;
    return lhs;
}

template <arithmetic T>
bool operator==(const Vec3<T> &lhs, const Vec3<T> &rhs) {
    return rhs.x == lhs.x && rhs.y == lhs.y && rhs.z == lhs.z;
}

template <arithmetic T>
std::ostream &operator<<(std::ostream &out, const Vec3<T> &vec) {
    return out << vec.x << " " << vec.y << " " << vec.z;
}
