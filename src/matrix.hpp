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

namespace cml {

template <typename T>
concept SquareMatrix = requires {
    { T::RowsCnt } -> std::convertible_to<unsigned int>;
    { T::ColsCnt } -> std::convertible_to<unsigned int>;
    requires T::RowsCnt == T::ColsCnt;
};

template <unsigned int Rows, unsigned int Cols, arithmetic T = default_type>
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
    Matrix<Rows, RHCols, T>
    operator*(const Matrix<Cols, RHCols, T> &rhs) const {
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

template <arithmetic T = default_type> using Mat4 = Matrix<4, 4, T>;
template <arithmetic T = default_type> using Mat3 = Matrix<3, 3, T>;
template <arithmetic T = default_type> using Mat2 = Matrix<2, 2, T>;
} // namespace cml
