#pragma once

#include "ow/cg/pbr_material.h"
#include "ow/math/vec2.h"
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
    std::vector<math::Vec2f> uvs;

    std::shared_ptr<PBRMaterial> material;

    static Mesh create_quad(){
        Mesh mesh;
        mesh.vertices = {
        math::Vec3f( 1.0F,  1.0F, 0.0F),  // top right
        math::Vec3f( 1.0F, -1.0F, 0.0F),  // bottom right
        math::Vec3f(-1.0F, -1.0F, 0.0F),  // bottom left
        math::Vec3f(-1.0F,  1.0F, 0.0F)  // top left 
        };

        mesh.uvs = {
            math::Vec2f( 1.0F, 1.0F),  // top right
            math::Vec2f( 1.0F, 0.0F),  // bottom right
            math::Vec2f( 0.0F, 0.0F),  // bottom left
            math::Vec2f( 0.0F, 1.0F)  // top left 
        };

        mesh.faces = {  // note that we start from 0!
            math::Vec3s(0, 1, 3),   // first triangle
            math::Vec3s(1, 2, 3)   // second triangle
        };

        mesh.normals = {
            math::Vec3f(0, 0, 1),
            math::Vec3f(0, 0, 1),
            math::Vec3f(0, 0, 1),
            math::Vec3f(0, 0, 1),
            math::Vec3f(0, 0, 1),
            math::Vec3f(0, 0, 1),
        };
        return mesh;
    }
};
}