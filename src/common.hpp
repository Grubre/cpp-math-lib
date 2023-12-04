#pragma once
#include <concepts>
#include <type_traits>

template <typename T>
concept arithmetic = std::is_arithmetic_v<T>;
