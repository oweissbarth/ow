#pragma once

#include <concepts>

namespace ow::math {

template<typename T>
concept Numeric = std::integral<T> or std::floating_point<T>;

}