
#include "mat4.h"
#include "mat3.h"
#include <cmath>
#include <cassert>

namespace ow::math{

    template<Numeric T>
    Mat4<T> Mat4<T>::perspective(double fov_radians, double aspect_ratio, double near, double far){
        T f = 1.0 / std::tan(fov_radians * static_cast<T>(0.5F));
        return Mat4<T>(
            f/aspect_ratio, 0, 0, 0,
            0, f, 0, 0,
            0, 0, (far+near)/(near-far), -1,
            0, 0, (2*far*near)/(near-far), 0
        );

    }

    
    template<Numeric T>
    template <Numeric U>
    Mat4<T> Mat4<T>::lookAt(Vec3<U> position, Vec3<U> target, Vec3<U> up){
        Vec3<T> f{(target - position).normalized()};
		Vec3<T> s{cross(f, up).normalized()};
		Vec3<T> u(cross(s, f));

		Mat4<T> view = Mat4<T>::identity();
		view(0, 0) = s.x;
		view(1, 0) = s.y;
		view(2, 0) = s.z;
		view(0, 1) = u.x;
		view(1, 1) = u.y;
		view(2, 1) = u.z;
		view(0, 2) =-f.x;
		view(1, 2) =-f.y;
		view(2, 2) =-f.z;
		view(3, 0) =-dot(s, position);
		view(3, 1) =-dot(u, position);
		view(3, 2) = dot(f, position);
		return view;
    }


    template<Numeric T>
    template<Numeric U>
    Mat4<T> Mat4<T>::operator*(const Mat4<U>& other) const
    {
        Mat4<T> result = Mat4<T>::zero();

        for (int col = 0; col < 4; ++col)
        {
            for (int row = 0; row < 4; ++row)
            {
                T sum = 0;
                for (int i = 0; i < 4; ++i)
                {
                    sum += m_data[row + 4 * i] * other.m_data[i + 4 * col];
                }
                result.m_data[row + 4 * col] = sum;
            }
        }
        return result;
    }

    template <Numeric T>
    T Mat4<T>::determinant() const {
        return m_data[0] * (m_data[5] * m_data[10] - m_data[6] * m_data[9]) -
                    m_data[1] * (m_data[4] * m_data[10] - m_data[6] * m_data[8]) +
                    m_data[2] * (m_data[4] * m_data[9] - m_data[5] * m_data[8]);
    }

    template <Numeric T>
    Mat4<T> Mat4<T>::inverse() const {
        Mat4<T> inv;

        T det = determinant();

        if (std::abs(det) < std::numeric_limits<float>::epsilon()) {
            // Matrix is not invertible, return the identity matrix
            return inv;
        }

         T invDet = static_cast<T>(1) / det;

        Mat4<T> invMat = Mat4<T>::zero();

        invMat.m_data[0] = (m_data[5] * m_data[10] - m_data[6] * m_data[9]) * invDet;
        invMat.m_data[1] = (m_data[2] * m_data[9] - m_data[1] * m_data[10]) * invDet;
        invMat.m_data[2] = (m_data[1] * m_data[6] - m_data[2] * m_data[5]) * invDet;
        invMat.m_data[3] = 0;

        invMat.m_data[4] = (m_data[6] * m_data[8] - m_data[4] * m_data[10]) * invDet;
        invMat.m_data[5] = (m_data[0] * m_data[10] - m_data[2] * m_data[8]) * invDet;
        invMat.m_data[6] = (m_data[2] * m_data[4] - m_data[0] * m_data[6]) * invDet;
        invMat.m_data[7] = 0;

        invMat.m_data[8] = (m_data[4] * m_data[9] - m_data[5] * m_data[8]) * invDet;
        invMat.m_data[9] = (m_data[1] * m_data[8] - m_data[0] * m_data[9]) * invDet;
        invMat.m_data[10] = (m_data[0] * m_data[5] - m_data[1] * m_data[4]) * invDet;
        invMat.m_data[11] = 0;

        invMat.m_data[12] = -(m_data[12] * invMat.m_data[0] + m_data[13] * invMat.m_data[4] + m_data[14] * invMat.m_data[8]);
        invMat.m_data[13] = -(m_data[12] * invMat.m_data[1] + m_data[13] * invMat.m_data[5] + m_data[14] * invMat.m_data[9]);
        invMat.m_data[14] = -(m_data[12] * invMat.m_data[2] + m_data[13] * invMat.m_data[6] + m_data[14] * invMat.m_data[10]);
        invMat.m_data[15] = 1;

        return invMat;
    }

    template <Numeric T>
    Mat4<T> Mat4<T>::transpose() const{
        Mat4<T> result;
        for (int i = 0; i < 4; ++i) {
            for (int j = i; j < 4; ++j) {
                result.m_data[i * 4 + j] = m_data[j * 4 + i];
                result.m_data[j * 4 + i] = m_data[i * 4 + j];
            }
        }
        return result;
    }

    template <Numeric T>
    Mat3<T> Mat4<T>::toMat3() const{
        return Mat3<T>(m_data[0], m_data[1], m_data[2],
                       m_data[4], m_data[5], m_data[6],
                       m_data[8], m_data[9], m_data[10]);
    }


    template <Numeric T>
    std::ostream& operator<<(std::ostream& os, const Mat4<T> &m){
        os << "Mat4x4(";
        for(int i = 0; i < 4; ++i){
            os << "(";
            for(int j = 0; j < 4; ++j){
                os << m(i,j);
                if(j != 3){
                    os<< ", ";
                }
            }
            if(i != 3){
                os << "),\n ";
            }else{
                os << ")";
            }
        }
        os << ")";
        return os;
    }

    // template instantiations
    template class Mat4<float>;
    template class Mat4<double>;
    template Mat4<double> Mat4<double>::operator*<double>(const Mat4<double>& other) const;
    template Mat4<float> Mat4<float>::operator*<float>(const Mat4<float>& other) const;
    template Mat4<float> Mat4<float>::lookAt(Vec3<float> position, Vec3<float> target, Vec3<float> up);
    template Mat4<double> Mat4<double>::lookAt(Vec3<double> position, Vec3<double> target, Vec3<double> up);
    template std::ostream& operator<<<float>(std::ostream& os, const Mat4<float> &m);
    template std::ostream& operator<<<double>(std::ostream& os, const Mat4<double> &m);
}

