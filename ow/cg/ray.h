#pragma once

#include "ow/math/vec3.h"
#include "ow/math/utils.h"
#include <cassert>

namespace ow::cg{

class Ray
{
public: 
    Ray() {}
    Ray(const math::Vec3f &origin, const math::Vec3f &direction): origin(origin), direction(direction) { assert(math::equals(direction.lengthSquared(), 1.0f));}

    math::Vec3f at(float t) const { return origin + t * direction; }

    math::Vec3f origin;
    math::Vec3f direction;

};

}