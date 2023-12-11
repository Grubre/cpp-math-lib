#pragma once
#include "common.hpp"
#include <array>
#include <cmath>
#include <concepts>
#include <iostream>
#include <ostream>

namespace cml {

using default_len_type = default_type;

template <arithmetic T, unsigned int Dim,
          std::floating_point LenT = default_len_type>
class Vec {
  public:
    constexpr Vec() : vals{0} {}
    constexpr Vec(std::initializer_list<T> list) {
        std::copy(list.begin(), list.end(), vals.begin());
    }
    template <unsigned int RHDim> explicit Vec(const Vec<T, RHDim, LenT> &rhs) {
        for (auto i = 0u; i < std::min(RHDim, Dim); i++) {
            vals[i] = rhs[i];
        }
    }

    constexpr Vec(T x, T y)
        requires(Dim == 2)
        : vals{x, y} {}
    constexpr Vec(T x, T y, T z)
        requires(Dim == 3)
        : vals{x, y, z} {}

    constexpr unsigned int dimension() const { return Dim; }

    constexpr T operator[](int i) const { return vals[i]; }
    constexpr T &operator[](int i) { return vals[i]; }

    constexpr T dot(const Vec &rhs) const {
        T sum = 0;
        for (int i = 0; i < Dim; i++) {
            sum += vals[i] * rhs.vals[i];
        }
        return sum;
    }

    constexpr LenT length_sq() const {
        LenT sum = 0;
        for (int i = 0; i < Dim; i++) {
            sum += vals[i] * vals[i];
        }
        return sum;
    }

    constexpr LenT length() const { return std::sqrt(length_sq()); }

    constexpr Vec<LenT, Dim, LenT> normalized() const {
        LenT len = length();
        Vec<LenT, Dim, LenT> normalized;
        for (int i = 0; i < Dim; i++) {
            normalized[i] = vals[i] / len;
        }
        return normalized;
    }

    constexpr Vec interpolated(LenT scalar) const {
        Vec interpolated;
        for (int i = 0; i < Dim; i++) {
            interpolated[i] = vals[i] * scalar;
        }
        return interpolated;
    }

    // clang-format off
    constexpr T x() const requires(Dim >= 1) { return vals[0]; }
    constexpr T &x() requires(Dim >= 1) { return vals[0]; }
    constexpr T y() const requires(Dim >= 2) { return vals[1]; }
    constexpr T &y() requires(Dim >= 2) { return vals[1]; }
    constexpr T z() const requires(Dim >= 3) { return vals[2]; }
    constexpr T &z() requires(Dim >= 3) { return vals[2]; }

    constexpr T r() const requires(Dim >= 1) { return vals[0]; }
    constexpr T &r() requires(Dim >= 1) { return vals[0]; }
    constexpr T g() const requires(Dim >= 2) { return vals[1]; }
    constexpr T &g() requires(Dim >= 2) { return vals[1]; }
    constexpr T b() const requires(Dim >= 3) { return vals[2]; }
    constexpr T &b() requires(Dim >= 3) { return vals[2]; }
    constexpr T a() const requires(Dim >= 4) { return vals[3]; }
    constexpr T &a() requires(Dim >= 4) { return vals[3]; }
    // clang-format on

    constexpr Vec perpendicular() const
        requires(Dim == 2)
    {
        return {-y(), x()};
    }

    class Iterator {
      public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T *;
        using reference = T &;

        Iterator(pointer ptr) : m_ptr(ptr) {}

        reference operator*() const { return *m_ptr; }
        pointer operator->() { return m_ptr; }

        Iterator &operator++() {
            m_ptr++;
            return *this;
        }

        Iterator operator++(int) {
            Iterator temp = *this;
            ++(*this);
            return temp;
        }

        friend bool operator==(const Iterator &a, const Iterator &b) {
            return a.m_ptr == b.m_ptr;
        };
        friend bool operator!=(const Iterator &a, const Iterator &b) {
            return a.m_ptr != b.m_ptr;
        };

      private:
        pointer m_ptr;
    };

    Iterator begin() { return Iterator(vals.begin()); }
    Iterator end() { return Iterator(vals.end()); }
    Iterator cbegin() const { return Iterator(vals.cbegin()); }
    Iterator cend() const { return Iterator(vals.cend()); }
    Iterator rbegin() { return Iterator(vals.rbegin()); }
    Iterator rend() const { return Iterator(vals.rend()); }
    Iterator crbegin() { return Iterator(vals.crbegin()); }
    Iterator crend() const { return Iterator(vals.crend()); }

    using LengthType = LenT;

  protected:
    std::array<T, Dim> vals;
};

template <arithmetic T, unsigned int Dim, std::floating_point LenT>
Vec<T, Dim, LenT> operator-(Vec<T, Dim, LenT> rhs) {
    for (auto i = 0u; i < Dim; i++) {
        rhs[i] = -rhs[i];
    }
    return rhs;
}

template <arithmetic T, unsigned int Dim, std::floating_point LenT>
Vec<T, Dim, LenT> operator+(Vec<T, Dim, LenT> lhs,
                            const Vec<T, Dim, LenT> &rhs) {
    for (auto i = 0u; i < Dim; i++) {
        lhs[i] += rhs[i];
    }
    return lhs;
}

template <arithmetic T, unsigned int Dim, std::floating_point LenT>
Vec<T, Dim, LenT> &operator+=(Vec<T, Dim, LenT> &lhs,
                              const Vec<T, Dim, LenT> &rhs) {
    for (auto i = 0u; i < Dim; i++) {
        lhs[i] += rhs[i];
    }
    return lhs;
}

template <arithmetic T, unsigned int Dim, std::floating_point LenT>
Vec<T, Dim, LenT> operator-(Vec<T, Dim, LenT> lhs,
                            const Vec<T, Dim, LenT> &rhs) {
    for (auto i = 0u; i < Dim; i++) {
        lhs[i] -= rhs[i];
    }
    return lhs;
}

template <arithmetic T, unsigned int Dim, std::floating_point LenT>
Vec<T, Dim, LenT> &operator-=(Vec<T, Dim, LenT> &lhs,
                              const Vec<T, Dim, LenT> &rhs) {
    for (auto i = 0u; i < Dim; i++) {
        lhs[i] -= rhs[i];
    }
    return lhs;
}

template <arithmetic T, unsigned int Dim, std::floating_point LenT>
Vec<T, Dim, LenT> operator*(T lhs, Vec<T, Dim, LenT> rhs) {
    for (auto i = 0u; i < Dim; i++) {
        rhs[i] *= lhs;
    }
    return rhs;
}

template <arithmetic T, unsigned int Dim, std::floating_point LenT>
Vec<T, Dim, LenT> operator*(const Vec<T, Dim, LenT> &lhs, T rhs) {
    return rhs * lhs;
}

template <arithmetic T, unsigned int Dim, std::floating_point LenT>
Vec<T, Dim, LenT> &operator*=(Vec<T, Dim, LenT> &lhs, const T rhs) {
    for (auto i = 0u; i < Dim; i++) {
        lhs[i] *= rhs;
    }
    return lhs;
}

template <arithmetic T, unsigned int Dim, std::floating_point LenT>
Vec<T, Dim, LenT> operator/(Vec<T, Dim, LenT> lhs, const T rhs) {
    for (auto i = 0u; i < Dim; i++) {
        lhs[i] /= rhs;
    }
    return lhs;
}

template <arithmetic T, unsigned int Dim, std::floating_point LenT>
Vec<T, Dim, LenT> &operator/=(Vec<T, Dim, LenT> &lhs, const T rhs) {
    for (auto i = 0u; i < Dim; i++) {
        lhs[i] /= rhs;
    }
    return lhs;
}

template <arithmetic T, unsigned int Dim, std::floating_point LenT>
bool operator==(const Vec<T, Dim, LenT> &lhs, const Vec<T, Dim, LenT> &rhs) {
    for (auto i = 0u; i < Dim; i++) {
        if (lhs[i] != rhs[i])
            return false;
    }
    return true;
}

template <arithmetic T, unsigned int Dim, std::floating_point LenT>
std::ostream &operator<<(std::ostream &out, const Vec<T, Dim, LenT> &vec) {
    for (auto i = 0u; i < Dim; i++) {
        out << vec[i];
        if (i < Dim - 1)
            out << " ";
    }
    return out;
}

template <arithmetic T, std::floating_point LenT = default_len_type>
using Vec3 = Vec<T, 3, LenT>;
using Vec3i = Vec3<int>;
using Vec3u = Vec3<unsigned int>;
using Vec3d = Vec3<double>;
using Vec3f = Vec3<float>;

template <arithmetic T, std::floating_point LenT = default_len_type>
using Vec2 = Vec<T, 2, LenT>;
using Vec2i = Vec2<int>;
using Vec2u = Vec2<unsigned int>;
using Vec2d = Vec2<double>;
using Vec2f = Vec2<float>;
} // namespace cml
