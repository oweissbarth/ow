#pragma once

#include "ow/math/vec3.h"

namespace ow::cg {

class PointLight {
    public:
        PointLight(const math::Vec3f& position, const math::Vec3f& color, float intensity);
    private:
        math::Vec3f position;
        math::Vec3f color;
        float intensity;
};

}