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

template <arithmetic T>
Matrix<4, 4, T> translate(const Matrix<4, 4, T> &matrix, Vec3<T> translation) {
    Matrix<4, 4, T> translation_matrix;
    translation_matrix[0][0] = 1;
    translation_matrix[0][1] = 0;
    translation_matrix[0][2] = 0;
    translation_matrix[0][3] = translation.x;
    translation_matrix[1][0] = 0;
    translation_matrix[1][1] = 1;
    translation_matrix[1][2] = 0;
    translation_matrix[1][3] = translation.y;
    translation_matrix[2][0] = 0;
    translation_matrix[2][1] = 0;
    translation_matrix[2][2] = 1;
    translation_matrix[2][3] = translation.z;
    translation_matrix[3][0] = 0;
    translation_matrix[3][1] = 0;
    translation_matrix[3][2] = 0;
    translation_matrix[3][3] = 1;
    return translation_matrix * matrix;
}

template <arithmetic T>
Matrix<4, 4, T> lookAt(Vec3<T> eye, Vec3<T> center, Vec3<T> up) {
    const auto f = (center - eye).normalized();
    const auto s = f.cross(up).normalized();
    const auto u = s.cross(f);
    Matrix<4, 4, T> look_at_matrix;
    look_at_matrix[0][0] = s.x;
    look_at_matrix[0][1] = u.x;
    look_at_matrix[0][2] = -f.x;
    look_at_matrix[0][3] = 0;
    look_at_matrix[1][0] = s.y;
    look_at_matrix[1][1] = u.y;
    look_at_matrix[1][2] = -f.y;
    look_at_matrix[1][3] = 0;
    look_at_matrix[2][0] = s.z;
    look_at_matrix[2][1] = u.z;
    look_at_matrix[2][2] = -f.z;
    look_at_matrix[2][3] = 0;
    look_at_matrix[3][0] = -s.dot(eye);
    look_at_matrix[3][1] = -u.dot(eye);
    look_at_matrix[3][2] = f.dot(eye);
    look_at_matrix[3][3] = 1;
    return look_at_matrix;
}

template <arithmetic T>
Matrix<4, 4, T> perspective(T fovy, T aspect, T near, T far) {
    const auto f = 1 / std::tan(fovy / 2);
    Matrix<4, 4, T> perspective_matrix;
    perspective_matrix[0][0] = f / aspect;
    perspective_matrix[0][1] = 0;
    perspective_matrix[0][2] = 0;
    perspective_matrix[0][3] = 0;
    perspective_matrix[1][0] = 0;
    perspective_matrix[1][1] = f;
    perspective_matrix[1][2] = 0;
    perspective_matrix[1][3] = 0;
    perspective_matrix[2][0] = 0;
    perspective_matrix[2][1] = 0;
    perspective_matrix[2][2] = (far + near) / (near - far);
    perspective_matrix[2][3] = -1;
    perspective_matrix[3][0] = 0;
    perspective_matrix[3][1] = 0;
    perspective_matrix[3][2] = (2 * far * near) / (near - far);
    perspective_matrix[3][3] = 0;
    return perspective_matrix;
}

} // namespace cml
