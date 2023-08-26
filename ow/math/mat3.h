#pragma once

#include <array>
#include <concepts>
#include <iostream>

#include "vec3.h"

#include "type_concepts.h"


namespace ow::math
{
template<Numeric T>
class Mat3{
    public:
    Mat3(const T xx, const T xy, const T xz, const T yx, const T yy, const T yz, const T zx, const T zy, const T zz){
        m_data = {xx, xy, xz, yx, yy, yz, zx, zy, zz};
    }

    static Mat3<T> identity(){
        return Mat3<T>(1, 0, 0,
                       0, 1, 0,
                       0, 0, 1);
    }

    static Mat3<T> zero(){
        return Mat3<T>(0, 0, 0,
                       0, 0, 0,
                       0, 0, 0);
    }

    const T* data() const{
        return m_data.data();
    }

    constexpr T& operator()(std::size_t col, std::size_t row) {
        return m_data[3 * col + row];
    }

    const T& operator()(std::size_t col, std::size_t row) const {
        return m_data[3 * col + row];
    }

    bool operator==(const Mat3<T>& other) const {
        for (int i = 0; i < DATASIZE; ++i) {
            if (m_data[i] != other.m_data[i]) {
                return false;
            }
        }
        return true;
    }

    bool operator!=(const Mat3<T>& other) const {
        return !(*this == other);
    }

    template <Numeric U>
    Mat3<T> operator*(const Mat3<U>& other) const;

    template <Numeric U>
    Vec3<T> operator*(const Vec3<U>& vec) const;

    T determinant() const;
    Mat3<T> inverse() const;

    Mat3<T> transpose() const;

    static const size_t DATASIZE = 9;

    private:

        // Column major order
        std::array<T, DATASIZE> m_data;
};

template<Numeric T>
std::ostream& operator<<(std::ostream& os, const Mat3<T> &m);

using Mat3f = Mat3<float>;

}