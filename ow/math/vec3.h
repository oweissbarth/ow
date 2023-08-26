#pragma once

#include "type_concepts.h"

#include <iostream>

namespace ow::math
{
template<Numeric T>
class Vec3{

public:

    Vec3(const T x, const T y, const T z): x(x), y(y), z(z) {};
    Vec3(): x(0), y(0), z(0) {};

    template<Numeric T2>
    explicit Vec3(const Vec3<T2>other): x(other.x), y(other.y), z(other.z) {};

    union {T x, r;};
    union {T y, g;};
    union {T z, b;};

    Vec3<T> operator-() const;
    Vec3<T>& operator+=(const Vec3<T> &v);

    Vec3<T>& operator*=(const T &c);
    Vec3<T>& operator/=(const T &c);

    T length() const;
    T lengthSquared() const;

    Vec3& normalized();
    void normalize();

    bool near_zero(T epsilon = 1e-8f) const;
   
};

template<Numeric T>
Vec3<T> operator+(const Vec3<T> &u, const Vec3<T> &v);

template<Numeric T>
Vec3<T> operator-(const Vec3<T> &u, const Vec3<T> &v);

template<Numeric T>
Vec3<T> operator*(const Vec3<T> &u, const Vec3<T> &v);

template<Numeric T>
Vec3<T> operator*(const T &c, const Vec3<T> &v);

template<Numeric T>
Vec3<T> operator*(const Vec3<T> &u, const T &c);

template<Numeric T>
Vec3<T> operator/(const Vec3<T> &u, const T &c);

template<Numeric T>
T dot(const Vec3<T> &u, const Vec3<T> &v);

template<Numeric T>
Vec3<T> cross(const Vec3<T> &u, const Vec3<T> &v);

template<Numeric T>
Vec3<T> reflect(const Vec3<T> &incoming, const Vec3<T> &normal);

template<Numeric T>
Vec3<T> refract(const Vec3<T> &incoming, const Vec3<T> &normal, float etai_over_etat);

template<Numeric T>
std::ostream& operator<<(std::ostream& os, const Vec3<T> &v);

using Vec3f = Vec3<float>;
using Vec3i = Vec3<int>;
using Vec3s = Vec3<short>;
using Vec3ui = Vec3<uint>;
}