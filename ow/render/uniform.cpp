#include "uniform.h"

#include <span>

namespace ow::render {

    template <math::Numeric T>
    Uniform<T>::Uniform(const std::string& name, T value)
        : m_name(name), m_type(UniformType::FLOAT) {
        set(value);
    }

    template <math::Numeric T>
    Uniform<T>::Uniform(const std::string& name, const math::Vec2<T>& value)
        : m_name(name), m_type(UniformType::VEC2) {
        set(value);
    }

    template <math::Numeric T>
    Uniform<T>::Uniform(const std::string& name, const math::Vec3<T>& value)
        : m_name(name), m_type(UniformType::VEC3) {
        set(value);
    }

    template <math::Numeric T>
    Uniform<T>::Uniform(const std::string& name, const math::Mat3<T>& value)
        : m_name(name), m_type(UniformType::MAT3) {
        set(value);
    }

    template <math::Numeric T>
    Uniform<T>::Uniform(const std::string& name, const math::Mat4<T>& value)
        : m_name(name), m_type(UniformType::MAT4) {
        set(value);
    }

    template <math::Numeric T>
    void Uniform<T>::set(T value) {
        m_values.clear();
        m_values.reserve(1);
        m_values.push_back(value);
    }

    template <math::Numeric T>
    void Uniform<T>::set(const math::Vec2<T>& value) {
        m_values.clear();
        m_values.reserve(2);
        m_values.push_back(value.x);
        m_values.push_back(value.y);
    }

    template <math::Numeric T>
    void Uniform<T>::set(const math::Vec3<T>& value) {
        m_values.clear();
        m_values.reserve(3);
        m_values.push_back(value.x);
        m_values.push_back(value.y);
        m_values.push_back(value.z);
    }

    template <math::Numeric T>
    void Uniform<T>::set(const math::Mat3<T>& value) {
        m_values.clear();
        m_values.reserve(value.DATASIZE);
        std::span value_span{value.data(), value.DATASIZE};
        m_values.assign(value_span.begin(), value_span.end());
    }

    template <math::Numeric T>
    void Uniform<T>::set(const math::Mat4<T>& value) {
        m_values.clear();
        m_values.reserve(value.DATASIZE);
        std::span value_span{value.data(), value.DATASIZE};
        m_values.assign(value_span.begin(), value_span.end());
    }

    template <math::Numeric T>
    const std::string& Uniform<T>::getName() const {
        return m_name;
    }

    template <math::Numeric T>
    UniformType Uniform<T>::getType() const {
        return m_type;
    }


    template <math::Numeric T>
    std::size_t Uniform<T>::getSize() const {
        return m_values.size();
    }

    template <math::Numeric T>
    const T* Uniform<T>::data() const {
        return m_values.data();
    }
} // namespace ow::render

template class ow::render::Uniform<float>;