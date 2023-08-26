#pragma once

#include "ow/cg/mesh.h"

namespace ow::render {
    struct Batch{
    cg::Mesh mesh;
    uint32_t shader_ref;
    uint32_t vao_ref;
};
}