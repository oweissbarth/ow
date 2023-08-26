#include "vec2.h"

#include <cmath>
#include <iostream>

namespace ow::math {
template <Numeric T> Vec2<T> Vec2<T>::operator-() const {
  return Vec2<T>(-x, -y);
}

template <Numeric T> Vec2<T> &Vec2<T>::operator+=(const Vec2<T> &v) {
  x += v.x;
  y += v.y;
  return *this;
}

template <Numeric T> Vec2<T>& Vec2<T>::operator*=(const T &t) {
  x *= t;
  y *= t;
  return *this;
}

template <Numeric T> Vec2<T> &Vec2<T>::operator/=(const T &c) {
  return *this *= 1 / c;
}

template <Numeric T> T Vec2<T>::length() const {
  return std::sqrt(lengthSquared());
}

template <Numeric T> T Vec2<T>::lengthSquared() const {
  return x * x + y * y;
}

template <Numeric T> Vec2<T> &Vec2<T>::normalized() {
  normalize();
  return *this;
}

template <Numeric T> void Vec2<T>::normalize() { *this /= length(); }

template <Numeric T> bool Vec2<T>::near_zero(T epsilon) const {
  return (std::fabs(x) < epsilon) && (std::fabs(y) < epsilon);
}

template <Numeric T> Vec2<T> operator+(const Vec2<T> &u, const Vec2<T> &v) {
  return Vec2(u.x + v.x, u.y + v.y);
}

template <Numeric T> Vec2<T> operator-(const Vec2<T> &u, const Vec2<T> &v) {
  return Vec2<T>(u.x - v.x, u.y - v.y);
}

template <Numeric T> Vec2<T> operator*(const Vec2<T> &u, const Vec2<T> &v) {
  return Vec2<T>(u.x * v.x, u.y * v.y);
}

template <Numeric T> Vec2<T> operator*(const T &c, const Vec2<T> &v) {
  return Vec2<T>(c * v.x, c * v.y);
}

template <Numeric T> Vec2<T> operator*(const Vec2<T> &u, const T &c) {
  return c * u;
}

template <Numeric T> Vec2<T> operator/(const Vec2<T> &u, const T &c) {
  return (1 / c) * u;
}


template <Numeric T>
std::ostream &operator<<(std::ostream &os, const Vec2<T> &v) {
  return os << "Vec2<T>(" << v.x << ", " << v.y << ")";
}

} // namespace ow::math

// Instantiate templates
template class ow::math::Vec2<float>;
template ow::math::Vec2<float> ow::math::operator+<float>(ow::math::Vec2<float> const&, ow::math::Vec2<float> const&);
template ow::math::Vec2<float> ow::math::operator-<float>(ow::math::Vec2<float> const&, ow::math::Vec2<float> const&);
template ow::math::Vec2<float> ow::math::operator*<float>(ow::math::Vec2<float> const&, ow::math::Vec2<float> const&);
template ow::math::Vec2<float> ow::math::operator*<float>(ow::math::Vec2<float> const&, float const&);
template ow::math::Vec2<float> ow::math::operator/<float>(ow::math::Vec2<float> const&, float const&);
template std::ostream &ow::math::operator<<<float>(std::ostream &os, const Vec2<float> &v);

template class ow::math::Vec2<int>;
template ow::math::Vec2<int> ow::math::operator+<int>(ow::math::Vec2<int> const&, ow::math::Vec2<int> const&);
template ow::math::Vec2<int> ow::math::operator-<int>(ow::math::Vec2<int> const&, ow::math::Vec2<int> const&);
template ow::math::Vec2<int> ow::math::operator*<int>(ow::math::Vec2<int> const&, ow::math::Vec2<int> const&);
template ow::math::Vec2<int> ow::math::operator*<int>(ow::math::Vec2<int> const&, int const&);
template std::ostream &ow::math::operator<<<int>(std::ostream &os, const Vec2<int> &v);
template std::ostream &ow::math::operator<<<short>(std::ostream &os, const Vec2<short> &v);
