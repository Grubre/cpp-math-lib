#pragma once
#include "common.hpp"
#include <algorithm>
#include <array>
#include <cmath>
#include <concepts>
#include <ostream>
#include <type_traits>

template <unsigned int Rows, unsigned int Cols, arithmetic T = double> class Matrix {
  public:
    Matrix() { std::fill(vals.begin(), vals.end(), T()); };
    Matrix(const Matrix &rhs) {
        std::copy(rhs.vals.begin(), rhs.vals.end(), vals.begin());
    }
    T &get(unsigned int x, unsigned int y) { return vals[x + y * Cols]; }
    T &operator()(unsigned int x, unsigned int y) { return get(x, y); }
    const T &get(unsigned int x, unsigned int y) const {
        return vals[x + y * Cols];
    }
    const T &operator()(unsigned int x, unsigned int y) const {
        return get(x, y);
    }

    Matrix transposed() const {
        Matrix t;
        for (int i = 0; i < Rows; i++) {
            for (int j = 0; j < Cols; j++) {
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
        for (int i = 0; i < Rows * Cols; i++) {
            matrix.vals[i] = vals[i] + rhs.vals[i];
        }
        return matrix;
    }

    Matrix &operator+=(const Matrix &rhs) {
        for (int i = 0; i < Rows * Cols; i++) {
            vals[i] = vals[i] + rhs.vals[i];
        }
        return *this;
    }

    Matrix operator-(const Matrix &rhs) {
        Matrix matrix;
        for (int i = 0; i < Rows * Cols; i++) {
            matrix.vals[i] = vals[i] - rhs.vals[i];
        }
        return matrix;
    }

    Matrix &operator-=(const Matrix &rhs) {
        for (int i = 0; i < Rows * Cols; i++) {
            vals[i] = vals[i] - rhs.vals[i];
        }
        return *this;
    }

    template <unsigned RHCols>
    Matrix<Rows, RHCols, T> operator*(const Matrix<Cols, RHCols, T> &rhs) {
        Matrix<Rows, RHCols, T> r;
        for (int i = 0; i < RHCols; i++) {
            for (int j = 0; j < Rows; j++) {
                T s = T();
                for (int k = 0; k < Cols; k++) {
                    s += vals[Cols * j + k] * vals[RHCols * k + i];
                }
                r.vals[j * RHCols + i] = s;
            }
        }
        return r;
    }

  protected:
    std::array<T, Rows * Cols> vals;
};
