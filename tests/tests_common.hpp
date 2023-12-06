#pragma once

#define ARITHMETIC_TYPES int, double, float, long double, unsigned int

template <typename T, unsigned int Dim> struct TypeDimPair {
    using Type = T;
    static constexpr unsigned int dim = Dim;
};

// clang-format off
#define ARITHMETIC_TYPES_AND_DIMS\
    TypeDimPair<int, 2>,\
    TypeDimPair<int, 3>,\
    TypeDimPair<int, 4>,\
    TypeDimPair<int, 5>,\
    TypeDimPair<int, 10>,\
    TypeDimPair<int, 20>,\
    TypeDimPair<double, 2>,\
    TypeDimPair<double, 3>,\
    TypeDimPair<double, 4>,\
    TypeDimPair<double, 5>,\
    TypeDimPair<double, 10>,\
    TypeDimPair<double, 20>,\
    TypeDimPair<float, 2>,\
    TypeDimPair<float, 3>,\
    TypeDimPair<float, 4>,\
    TypeDimPair<float, 5>,\
    TypeDimPair<float, 10>,\
    TypeDimPair<float, 20>,\
    TypeDimPair<long double, 2>,\
    TypeDimPair<long double, 3>,\
    TypeDimPair<long double, 4>,\
    TypeDimPair<long double, 5>,\
    TypeDimPair<long double, 10>,\
    TypeDimPair<long double, 20>,\
    TypeDimPair<unsigned int, 2>,\
    TypeDimPair<unsigned int, 3>,\
    TypeDimPair<unsigned int, 4>,\
    TypeDimPair<unsigned int, 5>,\
    TypeDimPair<unsigned int, 10>,\
    TypeDimPair<unsigned int, 20>
// clang-format on
