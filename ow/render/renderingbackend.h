#pragma once

#include <ow/cg/mesh.h>
#include "ow/render/uniform.h"
#include <ow/render/batch.h>
#include <ow/math/mat4.h>

namespace ow::render {



class RenderBackend {
public:
  [[nodiscard]] virtual bool init() const = 0;
  [[nodiscard]] virtual bool setup_viewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height) const = 0;
  [[nodiscard]] virtual bool clear() const = 0;
  [[nodiscard]] virtual bool buffer_geometry(Batch& batch) const = 0;
  [[nodiscard]] virtual bool prepare_shader(Batch& batch) const = 0;
  [[nodiscard]] virtual bool activate_shader(const Batch& batch) const = 0;
  [[nodiscard]] virtual bool deactivate_shader() const = 0;
  [[nodiscard]] virtual bool set_uniform(const uint32_t shader_ref, const Uniform<float>& uniform) const = 0;
  [[nodiscard]] virtual bool draw(const Batch& batch) const = 0;
};
} // namespace ow::render