#pragma once
#include "common.hpp"
#include <algorithm>
#include <array>
#include <cmath>
#include <concepts>
#include <initializer_list>
#include <ostream>
#include <span>
#include <type_traits>

template <unsigned int Rows, unsigned int Cols, arithmetic T = double>
class Matrix {
  public:
    Matrix() { std::fill(vals.begin(), vals.end(), T()); };
    Matrix(const std::initializer_list<T> &list) {
        std::copy(list.begin(), list.end(), vals.begin());
    }

    // TODO: Think whether mdspan is more appropriate since this addressing this
    // is in the form [y][x] and with mdspan it could be [x, y]
    std::span<T, Cols> operator[](unsigned int y) {
        return std::span<T, Cols>(vals.data() + y * Cols, Cols);
    }
    std::span<T const, Cols> operator[](unsigned int y) const {
        return std::span<T const, Cols>(vals.data() + y * Cols, Cols);
    }

    T &get(unsigned int y, unsigned int x) { return vals[x + y * Cols]; }
    const T &get(unsigned int y, unsigned int x) const {
        return vals[x + y * Cols];
    }

    Matrix<Cols, Rows, T> transposed() const {
        Matrix<Cols, Rows, T> t;
        for (int i = 0; i < Rows; i++) {
            for (int j = 0; j < Cols; j++) {
                t[j][i] = get(i, j);
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

template <unsigned int Rows, unsigned int Cols, arithmetic T>
std::ostream &operator<<(std::ostream &os, const Matrix<Rows, Cols, T> &m) {
    for (int i = 0; i < Rows; i++) {
        os << "[";
        for (int j = 0; j < Cols; j++) {
            os << m[i][j];
            if (j != Cols - 1)
                os << " ";
        }
        os << "]\n";
    }
    return os;
}
