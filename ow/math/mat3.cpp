#include "mat3.h"

#include <cassert>

namespace ow::math{

template<Numeric T>
template<Numeric U>
Mat3<T> Mat3<T>::operator*(const Mat3<U>& other) const
{
    Mat3<T> result(0, 0, 0, 0, 0, 0, 0, 0, 0);

    for (int col = 0; col < 3; ++col)
    {
        for (int row = 0; row < 3; ++row)
        {
            for (int i = 0; i < 3; ++i)
            {
                result.m_data[row + 3 * col] += m_data[row + 3 * i] * other.m_data[i + 3 * col];
            }
        }
    }
    return result;
}

template<Numeric T>
template<Numeric U>
Vec3<T> Mat3<T>::operator*(const Vec3<U>& vec) const
{
    Vec3<T> result(0, 0, 0);

    result.x = this->operator()(0, 0) * vec.x + this->operator()(1, 0) * vec.y + this->operator()(2, 0)*vec.z;
    result.y = this->operator()(0, 1) * vec.x + this->operator()(1, 1) * vec.y + this->operator()(2, 1)*vec.z;
    result.z = this->operator()(0, 2) * vec.x + this->operator()(1, 2) * vec.y + this->operator()(2, 2)*vec.z;
    return result;
}

template<Numeric T>
T Mat3<T>::determinant() const
{
    return m_data[0] * (m_data[4] * m_data[8] - m_data[5] * m_data[7])
        - m_data[1] * (m_data[3] * m_data[8] - m_data[5] * m_data[6])
        + m_data[2] * (m_data[3] * m_data[7] - m_data[4] * m_data[6]);
}

template<Numeric T>
Mat3<T> Mat3<T>::inverse() const
{
    T det = determinant();
    assert(det != 0);

    T invDet = static_cast<T>(1) / det;

    Mat3<T> invMat = Mat3<T>::zero();

    invMat.m_data[0] = (m_data[4] * m_data[8] - m_data[5] * m_data[7]) * invDet;
    invMat.m_data[1] = (m_data[2] * m_data[7] - m_data[1] * m_data[8]) * invDet;
    invMat.m_data[2] = (m_data[1] * m_data[5] - m_data[2] * m_data[4]) * invDet;

    invMat.m_data[3] = (m_data[5] * m_data[6] - m_data[3] * m_data[8]) * invDet;
    invMat.m_data[4] = (m_data[0] * m_data[8] - m_data[2] * m_data[6]) * invDet;
    invMat.m_data[5] = (m_data[2] * m_data[3] - m_data[0] * m_data[5]) * invDet;

    invMat.m_data[6] = (m_data[3] * m_data[7] - m_data[4] * m_data[6]) * invDet;
    invMat.m_data[7] = (m_data[1] * m_data[6] - m_data[0] * m_data[7]) * invDet;
    invMat.m_data[8] = (m_data[0] * m_data[4] - m_data[1] * m_data[3]) * invDet;

    return invMat;
}

template<Numeric T>
Mat3<T> Mat3<T>::transpose() const{
    Mat3<T> result(0, 0, 0, 0, 0, 0, 0, 0, 0);
    for(int col = 0; col < 3; ++col)
    {
        for(int row = 0; row < 3; ++row)
        {
            result.m_data[row + 3 * col] = m_data[col + 3 * row];
        }
    }

    return result;
}

template <Numeric T>
std::ostream& operator<<(std::ostream& os, const Mat3<T> &m){
    os << "Mat3x3(";
    for(int i = 0; i < 3; ++i){
        os << "(";
        for(int j = 0; j < 3; ++j){
            os << m(i,j);
            if(j != 2){
                os<< ", ";
            }
        }
        if(i != 2){
            os << "), ";
        }else{
            os << ")";
        }
    }
    os << ")";
    return os;
}


template class Mat3<float>;
template class Mat3<double>;
template Mat3<double> Mat3<double>::operator*<double>(const Mat3<double>& other) const;
template Mat3<float> Mat3<float>::operator*<float>(const Mat3<float>& other) const;
template Vec3<double> Mat3<double>::operator*<double>(const Vec3<double>& other) const;
template Vec3<float> Mat3<float>::operator*<float>(const Vec3<float>& other) const;
template std::ostream& operator<<<double>(std::ostream& os, const Mat3<double> &m);
template std::ostream& operator<<<float>(std::ostream& os, const Mat3<float> &m);


}
