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

template <typename T>
concept SquareMatrix = requires {
    { T::RowsCnt } -> std::convertible_to<unsigned int>;
    { T::ColsCnt } -> std::convertible_to<unsigned int>;
    requires T::RowsCnt == T::ColsCnt;
};

template <unsigned int Rows, unsigned int Cols, arithmetic T = double>
class Matrix {
  public:
    static constexpr auto RowsCnt = Rows;
    static constexpr auto ColsCnt = Cols;
    Matrix() { std::fill(vals.begin(), vals.end(), T()); };
    Matrix(const std::initializer_list<T> &list) {
        std::copy(list.begin(), list.end(), vals.begin());
    }

    // TODO: Think whether mdspan is more appropriate since this addressing this
    // is in the form [y][x] and with mdspan it could be [x, y]
    std::span<T, Cols> operator[](unsigned int row) {
        return std::span<T, Cols>(vals.data() + row * Cols, Cols);
    }
    std::span<T const, Cols> operator[](unsigned int row) const {
        return std::span<T const, Cols>(vals.data() + row * Cols, Cols);
    }

    T &get(unsigned int row, unsigned int col) {
        return vals[col + row * Cols];
    }
    const T &get(unsigned int row, unsigned int col) const {
        return vals[col + row * Cols];
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
        for (std::size_t i = 0; i < Rows * Cols; ++i) {
            matrix.vals[i] = -this->vals[i];
        }
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
            vals[i] += rhs.vals[i];
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
            vals[i] -= rhs.vals[i];
        }
        return *this;
    }

    // TODO: Consider transposing rhs to improve cache locality
    template <unsigned RHCols>
    Matrix<Rows, RHCols, T> operator*(const Matrix<Cols, RHCols, T> &rhs) {
        Matrix<Rows, RHCols, T> r;
        for (auto col = 0; col < RHCols; col++) {
            for (auto row = 0; row < Rows; row++) {
                T sum = T();
                for (auto k = 0u; k < Cols; k++) {
                    sum += get(row, k) * rhs.get(k, col);
                }
                r[row][col] = sum;
            }
        }
        return r;
    }

    Matrix operator*(const T &scalar) const {
        Matrix result;
        for (unsigned int i = 0; i < Rows; ++i) {
            for (unsigned int j = 0; j < Cols; ++j) {
                result[i][j] = get(i, j) * scalar;
            }
        }
        return result;
    }

    static Matrix identity()
        requires SquareMatrix<Matrix<Rows, Cols, T>>
    {
        Matrix id;
        for (unsigned int i = 0; i < Rows; ++i) {
            id[i][i] = T(1);
        }
        return id;
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
