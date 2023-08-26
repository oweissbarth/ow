#pragma once

#include "type_concepts.h"

#include "mat4.h"
#include "mat3.h"
#include "vec3.h"

#include <iostream>
#include <cmath>
#include <cassert>

namespace ow::math
{

template <Numeric T>
// A unit quaternion to represent rotations
class Quaternion {
public:
    T w, x, y, z;

    Quaternion(T w = 1, T x = 0, T y = 0, T z = 0)
    : w(w), x(x), y(y), z(z) {
        normalize();
    }

    static Quaternion fromAxisAngle(const T angle, Vec3<T> axis) {
        T halfAngle = angle / 2.;
        T sinHalfAngle = std::sin(halfAngle);

        auto normalizedAxis = axis.normalized();

        return Quaternion(std::cos(halfAngle), normalizedAxis.x * sinHalfAngle, normalizedAxis.y * sinHalfAngle, normalizedAxis.z * sinHalfAngle);
    }

    Quaternion operator+(const Quaternion& other) const {
        return Quaternion(w + other.w, x + other.x, y + other.y, z + other.z);
    }

    Quaternion operator-(const Quaternion& other) const {
        return Quaternion(w - other.w, x - other.x, y - other.y, z - other.z);
    }

    Quaternion operator*(const Quaternion& other) const {
        T new_w = w * other.w - x * other.x - y * other.y - z * other.z;
        T new_x = w * other.x + x * other.w + y * other.z - z * other.y;
        T new_y = w * other.y - x * other.z + y * other.w + z * other.x;
        T new_z = w * other.z + x * other.y - y * other.x + z * other.w;
        return Quaternion(new_w, new_x, new_y, new_z);
    }

    Quaternion operator*(T scalar) const {
        return Quaternion(w * scalar, x * scalar, y * scalar, z * scalar);
    }

    Quaternion conjugate() const {
        return Quaternion(w, -x, -y, -z);
    }

    T norm() const {
        return std::sqrt(w * w + x * x + y * y + z * z);
    }

    void normalize() {
        T n = norm();
        assert(n != 0);
        
        w /= n;
        x /= n;
        y /= n;
        z /= n;
    }

    Quaternion normalized() const {
        T n = norm();
        assert(n != 0);
        
        return Quaternion(w / n, x / n, y / n, z / n);
    }

    Mat4<T> toMat4() const {
        return Mat4<T>{
            1 - 2 * (y * y + z * z),
            2 * (x * y + z * w),
            2 * (x * z - y * w),
            0,

            2 * (x * y - z * w),
            1 - 2 * (x * x + z * z),
            2 * (y * z + x * w),
            0,

            2 * (x * z + y * w),
            2 * (y * z - x * w),
            1 - 2 * (x * x + y * y),
            0,

            0,
            0,
            0,
            1,
        };
    }

    Mat3<T> toMat3() const {
        return Mat3<T>{
            1 - 2 * (y * y + z * z),
            2 * (x * y + z * w),
            2 * (x * z - y * w),

            2 * (x * y - z * w),
            1 - 2 * (x * x + z * z),
            2 * (y * z + x * w),

            2 * (x * z + y * w),
            2 * (y * z - x * w),
            1 - 2 * (x * x + y * y)
        };
    }

    friend std::ostream& operator<<(std::ostream& os, const Quaternion& q) {
        os << q.w << " + " << q.x << "i + " << q.y << "j + " << q.z << "k";
        return os;
    }
};

using Quaternionf = Quaternion<float>;

}