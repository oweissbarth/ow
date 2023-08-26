#pragma once

#include <string>
#include <vector>

#include "ow/math/type_concepts.h"

#include "ow/math/vec2.h"
#include "ow/math/vec3.h"
#include "ow/math/mat3.h"
#include "ow/math/mat4.h"

namespace ow::render {

    enum class UniformType {
        FLOAT = 1,
        VEC2 = 2,
        VEC3 = 3,
        MAT3 = 9,
        MAT4 = 16
    };

    template <math::Numeric T>
    class Uniform {
    public:
        Uniform(const std::string& name, T value);
        Uniform(const std::string& name, const math::Vec2<T>& value);
        Uniform(const std::string& name, const math::Vec3<T>& value);
        Uniform(const std::string& name, const math::Mat3<T>& value);
        Uniform(const std::string& name, const math::Mat4<T>& value);

        ~Uniform() = default;

        void set(T value);
        void set(const math::Vec2<T>& value);
        void set(const math::Vec3<T>& value);
        void set(const math::Mat3<T>& value);
        void set(const math::Mat4<T>& value);

        [[nodiscard]] const std::string& getName() const;
        [[nodiscard]] UniformType getType() const;
        [[nodiscard]] std::size_t getSize() const;

        [[nodiscard]] const T* data() const;

    private:
        std::string m_name;
        UniformType m_type;
        std::vector<T> m_values;
    };

}