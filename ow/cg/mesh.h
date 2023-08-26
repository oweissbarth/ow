#pragma once

#include "ow/cg/pbr_material.h"
#include "ow/math/vec3.h"
#include <vector>
#include <memory>

namespace ow::cg
{

struct Mesh
{
    std::vector<math::Vec3f> vertices;
    std::vector<math::Vec3f> normals;
    std::vector<math::Vec3<short>> faces;

    std::shared_ptr<PBRMaterial> material;
};
}