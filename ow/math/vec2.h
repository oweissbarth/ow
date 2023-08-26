#pragma once

#include "type_concepts.h"

#include <iostream>

namespace ow::math
{
template<Numeric T>
class Vec2{

public:

    Vec2(const T x, const T y): x(x), y(y) {};
    Vec2(): x(0), y(0){};

    template<Numeric T2>
    explicit Vec2(const Vec2<T2>other): x(other.x), y(other.y) {};

    T x;
    T y;

    Vec2<T> operator-() const;
    Vec2<T>& operator+=(const Vec2<T> &v);

    Vec2<T>& operator*=(const T &c);
    Vec2<T>& operator/=(const T &c);

    T length() const;
    T lengthSquared() const;

    Vec2& normalized();
    void normalize();

    bool near_zero(T epsilon = 1e-8f) const;
   
};

template<Numeric T>
Vec2<T> operator+(const Vec2<T> &u, const Vec2<T> &v);

template<Numeric T>
Vec2<T> operator-(const Vec2<T> &u, const Vec2<T> &v);

template<Numeric T>
Vec2<T> operator*(const Vec2<T> &u, const Vec2<T> &v);

template<Numeric T>
Vec2<T> operator*(const T &c, const Vec2<T> &v);

template<Numeric T>
Vec2<T> operator*(const Vec2<T> &u, const T &c);

template<Numeric T>
Vec2<T> operator/(const Vec2<T> &u, const T &c);

template<Numeric T>
std::ostream& operator<<(std::ostream& os, const Vec2<T> &v);

using Vec2f = Vec2<float>;
using Vec2i = Vec2<int>;
using Vec2s = Vec2<short>;
using Vec2ui = Vec2<uint>;
}