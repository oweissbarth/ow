#pragma once

#include <array>
#include <concepts>
#include <iostream>

#include "mat3.h"
#include "vec3.h"
#include "type_concepts.h"


namespace ow::math
{
template<Numeric T>
class Mat4{
    public:
    Mat4(const T xx, const T xy, const T xz, const T xw, const T yx, const T yy, const T yz, const T yw, const T zx, const T zy, const T zz, const T zw, const T wx, const T wy, const T wz, const T ww){
        m_data = {xx, xy, xz, xw, yx, yy, yz, yw, zx, zy, zz, zw, wx, wy, wz, ww};
    }

    static Mat4<T> identity(){
        return Mat4<T>(1, 0, 0, 0,
                       0, 1, 0, 0,
                       0, 0, 1, 0,
                       0, 0, 0, 1);
    }

    static Mat4<T> zero(){
        return Mat4<T>(0, 0, 0, 0,
                       0, 0, 0, 0,
                       0, 0, 0, 0,
                       0, 0, 0, 0);
    }

    Mat4() {
        m_data = {1, 0, 0, 0,
                    0, 1, 0, 0,
                    0, 0, 1, 0,
                    0, 0, 0, 1};
    }

    const T* data() const{
        return m_data.data();
    }

    constexpr T& operator()(std::size_t col, std::size_t row) {
        return m_data[4 * col + row];
    }

    const T& operator()(std::size_t col, std::size_t row) const {
        return m_data[4 * col + row];
    }

    bool operator==(const Mat4<T>& other) const {
        for (int i = 0; i < DATASIZE; ++i) {
            if (m_data[i] != other.m_data[i]) {
                return false;
            }
        }
        return true;
    }

    bool operator!=(const Mat4<T>& other) const {
        return !(*this == other);
    }

    template <Numeric U>
    Mat4<T> operator*(const Mat4<U>& other) const;

    T determinant() const;
    Mat4<T> inverse() const;
    Mat4<T> transpose() const;

    Mat3<T> toMat3() const;

    static Mat4<T> perspective(double fov, double aspect_ratio, double near, double far);

    template <Numeric U>
    static Mat4<T> lookAt(Vec3<U> position, Vec3<U> target, Vec3<U> up);

    static const size_t DATASIZE = 16;

    private:
       std::array<T, DATASIZE> m_data;
};

template<Numeric T>
std::ostream& operator<<(std::ostream& os, const Mat4<T> &m);

using Mat4f = Mat4<float>;

}