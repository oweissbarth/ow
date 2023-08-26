#pragma once

#include "ow/math/vec3.h"

namespace ow::cg
{
    struct PBRMaterial
    {
        math::Vec3f albedo{0.5F,0.5F,0.5F};
        float metallic{1.F};
        float roughness{1.F};
        math::Vec3f emissive {0.F,0.F,0.F};
    };
}