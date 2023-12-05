#pragma once
#include <concepts>
#include <type_traits>

namespace cml {

template <typename T>
concept arithmetic = std::is_arithmetic_v<T>;

using default_type = double;

} // namespace cml
