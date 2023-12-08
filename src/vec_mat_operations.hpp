#pragma once
#include "common.hpp"
#include "matrix.hpp"
#include "vector.hpp"

namespace cml {

template <arithmetic T, unsigned int Dim> using ColumnVec = Matrix<Dim, 1, T>;

template <arithmetic T, unsigned int Rows, unsigned int Cols,
          std::floating_point LenT>
Vec<T, Rows, LenT> operator*(const Matrix<Rows, Cols, T> &lhs,
                             const Vec<T, Cols, LenT> &rhs) {
    const auto rhs_as_mat = *reinterpret_cast<const ColumnVec<T, Cols> *>(&rhs);
    const auto result = lhs * rhs_as_mat;
    return *reinterpret_cast<const Vec<T, Rows, LenT> *>(&result);
}

} // namespace cml
