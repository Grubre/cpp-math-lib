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

template <arithmetic T>
Matrix<4, 4, T> rotate(const Matrix<4, 4, T> &matrix, T angle, Vec3<T> axis) {
    const auto c = std::cos(angle);
    const auto s = std::sin(angle);
    const auto t = 1 - c;
    const auto x = axis.x;
    const auto y = axis.y;
    const auto z = axis.z;
    const auto tx = t * x;
    const auto ty = t * y;
    const auto tz = t * z;
    const auto txy = tx * y;
    const auto txz = tx * z;
    const auto tyz = ty * z;
    const auto sx = s * x;
    const auto sy = s * y;
    const auto sz = s * z;
    Matrix<4, 4, T> rotation_matrix;
    rotation_matrix[0][0] = c + tx * x;
    rotation_matrix[0][1] = txy - sz;
    rotation_matrix[0][2] = txz + sy;
    rotation_matrix[0][3] = 0;
    rotation_matrix[1][0] = txy + sz;
    rotation_matrix[1][1] = c + ty * y;
    rotation_matrix[1][2] = tyz - sx;
    rotation_matrix[1][3] = 0;
    rotation_matrix[2][0] = txz - sy;
    rotation_matrix[2][1] = tyz + sx;
    rotation_matrix[2][2] = c + tz * z;
    rotation_matrix[2][3] = 0;
    rotation_matrix[3][0] = 0;
    rotation_matrix[3][1] = 0;
    rotation_matrix[3][2] = 0;
    rotation_matrix[3][3] = 1;
    return rotation_matrix * matrix;
}
} // namespace cml
