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

TEST_CASE_TEMPLATE("Vec Matrix Operations: operator * (LHS Mat, RHS vec)", T, ARITHMETIC_TYPES_AND_DIMS) {
    SUBCASE("Zero Matrix and Non-Zero Vector") {
        Matrix<T::dim, T::dim, TT> A;

        Vec<TT, T::dim> x;
        std::iota(x.begin(), x.end(), TT(0));

        auto b = A * x;

        for (auto i = 0u; i < T::dim; i++) {
            CHECK(b[i] == TT(0));
        }
    }

    SUBCASE("Identity Matrix and Arbitrary Vector") {
        Matrix<T::dim, T::dim, TT> A = Matrix<T::dim, T::dim, TT>::identity();
        Vec<TT, T::dim> x;
        std::iota(x.begin(), x.end(), TT(1));

        Vec<TT, T::dim> b = A * x;
        for (auto i = 0u; i < T::dim; i++) {
            CHECK(b[i] == x[i]);
        }
    }

    SUBCASE("Arbitrary Matrix and Zero Vector") {
        Matrix<T::dim, T::dim, TT> A;
        std::iota(A.begin(), A.end(), TT(1));
        Vec<TT, T::dim> x; 

        Vec<TT, T::dim> b = A * x;
        for (auto i = 0u; i < T::dim; i++) {
            CHECK(b[i] == TT(0));
        }
    }
}
