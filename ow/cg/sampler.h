#pragma once

#include "ow/math/vec3.h"

namespace ow::cg
{


float random_float(float min = 0, float max = 1.0);

math::Vec3f random(float min = 0, float max = 1.0);

math::Vec3f random_in_unit_sphere();

math::Vec3f random_in_unit_disk();

math::Vec3f random_unit_vector();

math::Vec3f random_in_hemisphere(const math::Vec3f &normal);

    
}