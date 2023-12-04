#pragma once
#include "common.hpp"
#include "matrix.hpp"
#include <array>
#include <cmath>
#include <concepts>
#include <ostream>

template <arithmetic T, unsigned int Dim, std::floating_point F = double>
class Vec {
  public:
    constexpr Vec() : vals{0} {}
    template <unsigned int RHDim> explicit Vec(const Vec<T, RHDim, F> &rhs) {
        for (auto i = 0u; i < std::min(RHDim, Dim); i++) {
            vals[i] = rhs[i];
        }
    }

    constexpr T &operator[](int i) const { return vals[i]; }
    constexpr T &operator[](int i) { return vals[i]; }

    constexpr T dot(const Vec<T, Dim, F> &rhs) const {
        T sum = 0;
        for (int i = 0; i < Dim; i++) {
            sum += vals[i] * rhs.vals[i];
        }
        return sum;
    }

    constexpr F length_sq() const {
        F sum = 0;
        for (int i = 0; i < Dim; i++) {
            sum += vals[i] * vals[i];
        }
        return sum;
    }

    constexpr F length() const { return std::sqrt(length_sq()); }

    constexpr Vec<F, Dim, F> normalized() const {
        F len = length();
        Vec<F, Dim, F> normalized;
        for (int i = 0; i < Dim; i++) {
            normalized[i] = vals[i] / len;
        }
        return normalized;
    }

    constexpr Vec<F, Dim, F> interpolate(F scalar) const {
        Vec<F, Dim, F> interpolated;
        for (int i = 0; i < Dim; i++) {
            interpolated.vals[i] = vals[i] * scalar;
        }
        return interpolated;
    }

  protected:
    std::array<T, Dim> vals;
};

template <arithmetic T, unsigned int Dim, std::floating_point F>
Vec<T, Dim, F> operator-(Vec<T, Dim, F> rhs) {
    for (auto i = 0u; i < Dim; i++) {
        rhs[i] = -rhs[i];
    }
    return rhs;
}

template <arithmetic T, unsigned int Dim, std::floating_point F>
Vec<T, Dim, F> operator+(Vec<T, Dim, F> lhs, const Vec<T, Dim, F> &rhs) {
    for (auto i = 0u; i < Dim; i++) {
        lhs[i] += rhs[i];
    }
    return lhs;
}

template <arithmetic T, unsigned int Dim, std::floating_point F>
Vec<T, Dim, F> &operator+=(Vec<T, Dim, F> &lhs, const Vec<T, Dim, F> &rhs) {
    for (auto i = 0u; i < Dim; i++) {
        lhs[i] += rhs[i];
    }
    return lhs;
}

template <arithmetic T, unsigned int Dim, std::floating_point F>
Vec<T, Dim, F> operator-(Vec<T, Dim, F> lhs, const Vec<T, Dim, F> &rhs) {
    for (auto i = 0u; i < Dim; i++) {
        lhs[i] -= rhs[i];
    }
    return lhs;
}

template <arithmetic T, unsigned int Dim, std::floating_point F>
Vec<T, Dim, F> &operator-=(Vec<T, Dim, F> &lhs, const Vec<T, Dim, F> &rhs) {
    for (auto i = 0u; i < Dim; i++) {
        lhs[i] -= rhs[i];
    }
    return lhs;
}

template <arithmetic T, unsigned int Dim, std::floating_point F>
Vec<T, Dim, F> operator*(T lhs, const Vec<T, Dim, F> &rhs) {
    for (auto i = 0u; i < Dim; i++) {
        lhs[i] *= rhs[i];
    }
    return lhs;
}

template <arithmetic T, unsigned int Dim, std::floating_point F>
Vec<T, Dim, F> operator*(const Vec<T, Dim, F> &lhs, T rhs) {
    return rhs * lhs;
}

template <arithmetic T, unsigned int Dim, std::floating_point F>
Vec<T, Dim, F> &operator*=(Vec<T, Dim, F> &lhs, const T rhs) {
    for (auto i = 0u; i < Dim; i++) {
        lhs[i] *= rhs[i];
    }
    return lhs;
}

template <arithmetic T, unsigned int Dim, std::floating_point F>
Vec<T, Dim, F> operator/(const Vec<T, Dim, F> &lhs, T rhs) {
    for (auto i = 0u; i < Dim; i++) {
        lhs[i] /= rhs[i];
    }
    return lhs;
}

template <arithmetic T, unsigned int Dim, std::floating_point F>
Vec<T, Dim, F> &operator/=(Vec<T, Dim, F> &lhs, const T rhs) {
    for (auto i = 0u; i < Dim; i++) {
        lhs[i] /= rhs[i];
    }
    return lhs;
}

template <arithmetic T, unsigned int Dim, std::floating_point F>
bool operator==(const Vec<T, Dim, F> &lhs, const Vec<T, Dim, F> &rhs) {
    for (auto i = 0u; i < Dim; i++) {
        if (lhs[i] != rhs[i])
            return false;
    }
    return true;
}

template <arithmetic T, unsigned int Dim, std::floating_point F>
std::ostream &operator<<(std::ostream &out, const Vec<T, Dim, F> &vec) {
    for (auto i = 0u; i < Dim; i++) {
        out << vec[i];
        if (i < Dim - 1)
            out << " ";
    }
    return out;
}

template <arithmetic T, std::floating_point F = double> class Vec2;
template <arithmetic T, std::floating_point F = double> class Vec3;

template <arithmetic T, std::floating_point F>
class Vec3 : public Vec<T, 3, F> {
  public:
    T &x = this->vals[0];
    T &y = this->vals[1];
    T &z = this->vals[2];

    constexpr Vec3() : Vec<T, 3, F>{} {}
    constexpr Vec3(T x, T y, T z) {this->vals ={x,y,z}; }
    constexpr Vec3(Vec3 const &rhs) {this->vals = rhs.vals; this->x = this->vals[0]; this->y = this->vals[1]; this->z = this->vals[2];}
};

using Vec3i = Vec3<int>;
using Vec3u = Vec3<unsigned int>;
using Vec3d = Vec3<double>;
using Vec3f = Vec3<float>;

template <arithmetic T, std::floating_point F>
class Vec2 : public Vec<T, 2, F> {
  public:
    T &x = this->vals[0];
    T &y = this->vals[1];

    constexpr Vec2() : Vec<T, 2, F>{} {}
    constexpr Vec2(T x, T y) {this->vals = {x,y};}
    constexpr Vec2(Vec2 const &rhs) {this->vals = rhs.vals; this->x = this->vals[0]; this->y = this->vals[1];}

    constexpr Vec2<T> perpendicular() const { return {-y, x}; }
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
