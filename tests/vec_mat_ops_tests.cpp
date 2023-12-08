#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"
#include "matrix.hpp"
#include "tests_common.hpp"
#include "vec_mat_operations.hpp"
#include "vector.hpp"
#include <array>
#include <numeric>

using namespace cml;

#define TT typename T::Type

TEST_CASE_TEMPLATE("Vec Matrix Operations: operator *", T,
                   ARITHMETIC_TYPES_AND_DIMS) {
    Matrix<T::dim, T::dim, TT> A;
    std::iota(A.begin(), A.end(), TT(0));

    Vec<TT, T::dim> x;
    std::iota(x.begin(), x.end(), TT(0));

    Vec<TT, T::dim> b = A * x;

    for (auto i = 0u; i < T::dim; i++) {
        CHECK(b[i] == TT(2 * i + 1));
    }
}
