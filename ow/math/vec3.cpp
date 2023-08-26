#include "vec3.h"

#include <cmath>
#include <iostream>

namespace ow::math {
template <Numeric T> Vec3<T> Vec3<T>::operator-() const {
  return Vec3<T>(-x, -y, -z);
}

template <Numeric T> Vec3<T> &Vec3<T>::operator+=(const Vec3<T> &v) {
  x += v.x;
  y += v.y;
  z += v.z;
  return *this;
}

template <Numeric T> Vec3<T>& Vec3<T>::operator*=(const T &t) {
  x *= t;
  y *= t;
  z *= t;
  return *this;
}

template <Numeric T> Vec3<T> &Vec3<T>::operator/=(const T &c) {
  return *this *= 1 / c;
}

template <Numeric T> T Vec3<T>::length() const {
  return std::sqrt(lengthSquared());
}

template <Numeric T> T Vec3<T>::lengthSquared() const {
  return x * x + y * y + z * z;
}

template <Numeric T> Vec3<T> &Vec3<T>::normalized() {
  normalize();
  return *this;
}

template <Numeric T> void Vec3<T>::normalize() { *this /= length(); }

template <Numeric T> bool Vec3<T>::near_zero(T epsilon) const {
  return (std::fabs(x) < epsilon) && (std::fabs(y) < epsilon) && (std::fabs(z) < epsilon);
}

template <Numeric T> Vec3<T> operator+(const Vec3<T> &u, const Vec3<T> &v) {
  return Vec3(u.x + v.x, u.y + v.y, u.z + v.z);
}

template <Numeric T> Vec3<T> operator-(const Vec3<T> &u, const Vec3<T> &v) {
  return Vec3<T>(u.x - v.x, u.y - v.y, u.z - v.z);
}

template <Numeric T> Vec3<T> operator*(const Vec3<T> &u, const Vec3<T> &v) {
  return Vec3<T>(u.x * v.x, u.y * v.y, u.z * v.z);
}

template <Numeric T> Vec3<T> operator*(const T &c, const Vec3<T> &v) {
  return Vec3<T>(c * v.x, c * v.y, c * v.z);
}

template <Numeric T> Vec3<T> operator*(const Vec3<T> &u, const T &c) {
  return c * u;
}

template <Numeric T> Vec3<T> operator/(const Vec3<T> &u, const T &c) {
  return (1 / c) * u;
}

template <Numeric T> T dot(const Vec3<T> &u, const Vec3<T> &v) {
  return u.x * v.x + u.y * v.y + u.z * v.z;
}

template <Numeric T> Vec3<T> cross(const Vec3<T> &u, const Vec3<T> &v) {
  return Vec3(u.y * v.z - u.z * v.y, u.z * v.x - u.x * v.z,
              u.x * v.y - u.y * v.x);
}

template <Numeric T>
Vec3<T> reflect(const Vec3<T> &incoming, const Vec3<T> &normal) {
  return incoming - 2 * dot(incoming, normal) * normal;
}

template <Numeric T>
Vec3<T> refract(const Vec3<T> &incoming, const Vec3<T> &normal,
                float etai_over_etat) {
  float cos_theta = std::fmin(dot(-incoming, normal), 1.0f);
  Vec3<T> r_out_perp = etai_over_etat * (incoming + cos_theta * normal);
  Vec3<T> r_out_parallel =
      (-std::sqrt(std::fabs(1.0f - r_out_perp.lengthSquared()))) * normal;
  return r_out_perp + r_out_parallel;
}

template <Numeric T>
std::ostream &operator<<(std::ostream &os, const Vec3<T> &v) {
  return os << "Vec3<T>(" << v.x << ", " << v.y << ", " << v.z << ")";
}

} // namespace ow::math

// Instantiate templates
template class ow::math::Vec3<float>;
template class ow::math::Vec3<double>;
template ow::math::Vec3<float> ow::math::operator+<float>(ow::math::Vec3<float> const&, ow::math::Vec3<float> const&);
template ow::math::Vec3<float> ow::math::operator-<float>(ow::math::Vec3<float> const&, ow::math::Vec3<float> const&);
template ow::math::Vec3<float> ow::math::operator*<float>(ow::math::Vec3<float> const&, ow::math::Vec3<float> const&);
template ow::math::Vec3<float> ow::math::operator*<float>(ow::math::Vec3<float> const&, float const&);
template ow::math::Vec3<float> ow::math::operator*<float>(float const&, ow::math::Vec3<float> const&);
template ow::math::Vec3<float> ow::math::operator/<float>(ow::math::Vec3<float> const&, float const&);
template ow::math::Vec3<double> ow::math::operator+<double>(ow::math::Vec3<double> const&, ow::math::Vec3<double> const&);
template ow::math::Vec3<double> ow::math::operator-<double>(ow::math::Vec3<double> const&, ow::math::Vec3<double> const&);
template ow::math::Vec3<double> ow::math::operator*<double>(ow::math::Vec3<double> const&, ow::math::Vec3<double> const&);
template ow::math::Vec3<double> ow::math::operator*<double>(ow::math::Vec3<double> const&, double const&);
template ow::math::Vec3<double> ow::math::operator/<double>(ow::math::Vec3<double> const&, double const&);
template std::ostream &ow::math::operator<<<float>(std::ostream &os, const Vec3<float> &v);
template ow::math::Vec3<float> ow::math::cross(const Vec3<float> &u, const Vec3<float> &v);
template float ow::math::dot(const Vec3<float> &u, const Vec3<float> &v);
template ow::math::Vec3<double> ow::math::cross(const Vec3<double> &u, const Vec3<double> &v);
template double ow::math::dot(const Vec3<double> &u, const Vec3<double> &v);
template ow::math::Vec3<float> ow::math::reflect(const Vec3<float> &incoming, const Vec3<float> &normal);
template ow::math::Vec3<float> ow::math::refract(const Vec3<float> &incoming, const Vec3<float> &normal, float etai_over_etat);


template class ow::math::Vec3<int>;
template ow::math::Vec3<int> ow::math::operator+<int>(ow::math::Vec3<int> const&, ow::math::Vec3<int> const&);
template ow::math::Vec3<int> ow::math::operator-<int>(ow::math::Vec3<int> const&, ow::math::Vec3<int> const&);
template ow::math::Vec3<int> ow::math::operator*<int>(ow::math::Vec3<int> const&, ow::math::Vec3<int> const&);
template ow::math::Vec3<int> ow::math::operator*<int>(ow::math::Vec3<int> const&, int const&);
template std::ostream &ow::math::operator<<<int>(std::ostream &os, const Vec3<int> &v);
template std::ostream &ow::math::operator<<<short>(std::ostream &os, const Vec3<short> &v);
