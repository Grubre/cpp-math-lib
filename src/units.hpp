#pragma once
#include "common.hpp"
#include "constants.hpp"

namespace cml {

template <arithmetic T> auto radians(T deg) { return deg * pi<T> / 180; }
template <arithmetic T> auto degrees(T rad) { return rad * 180 / pi<T>; }
} // namespace cml
