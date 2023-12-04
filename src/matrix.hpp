#pragma once
#include "common.hpp"
#include <algorithm>
#include <array>
#include <cmath>
#include <concepts>
#include <ostream>
#include <type_traits>

template <unsigned int R, unsigned int C, arithmetic T = float> class Matrix {
  public:
    Matrix() { std::fill(vals.begin(), vals.end(), T()); };
    Matrix(const Matrix &rhs) {
        std::copy(rhs.vals.begin(), rhs.vals.end(), vals.begin());
    }
    T &get(unsigned int x, unsigned int y) { return vals[x + y * C]; }
    T &operator()(unsigned int x, unsigned int y) { return get(x, y); }
    const T &get(unsigned int x, unsigned int y) const {
        return vals[x + y * C];
    }
    const T &operator()(unsigned int x, unsigned int y) const {
        return get(x, y);
    }

    Matrix transposed() const {
        Matrix t;
        for (int i = 0; i < R; i++) {
            for (int j = 0; j < C; j++) {
                t.vals[j][i] = vals[i][j];
            }
        }
        return t;
    }

    Matrix operator-() {
        Matrix matrix;
        std::for_each(matrix.vals.begin(), matrix.vals.end(),
                      [i = 0, this](T &val) mutable {
                          val = -this->vals[i];
                          ++i;
                      });
        return matrix;
    }

    Matrix operator+(const Matrix &rhs) {
        Matrix matrix;
        for (int i = 0; i < R * C; i++) {
            matrix.vals[i] = vals[i] + rhs.vals[i];
        }
        return matrix;
    }

    Matrix &operator+=(const Matrix &rhs) {
        for (int i = 0; i < R * C; i++) {
            vals[i] = vals[i] + rhs.vals[i];
        }
        return *this;
    }

    Matrix operator-(const Matrix &rhs) {
        Matrix matrix;
        for (int i = 0; i < R * C; i++) {
            matrix.vals[i] = vals[i] - rhs.vals[i];
        }
        return matrix;
    }

    Matrix &operator-=(const Matrix &rhs) {
        for (int i = 0; i < R * C; i++) {
            vals[i] = vals[i] - rhs.vals[i];
        }
        return *this;
    }

    template <unsigned bC>
    Matrix<R, bC, T> operator*(const Matrix<C, bC, T> &rhs) {
        Matrix<R, bC, T> r;
        for (int i = 0; i < bC; i++) {
            for (int j = 0; j < R; j++) {
                T s = T();
                for (int k = 0; k < C; k++) {
                    s += vals[C * j + k] * vals[bC * k + i];
                }
                r.vals[j * bC + i] = s;
            }
        }
        return r;
    }

  protected:
    std::array<T, R * C> vals;
};
