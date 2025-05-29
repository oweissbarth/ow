#pragma once

#include <ow/cg/mesh.h>
#include "ow/render/uniform.h"
#include <ow/render/batch.h>
#include <ow/math/mat4.h>
#include <ow/cg/image.h>
#include <ow/render/shader.h>

namespace ow::render {



class RenderBackend {
public:
  [[nodiscard]] virtual bool init() const = 0;
  [[nodiscard]] virtual bool setup_viewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height) const = 0;
  [[nodiscard]] virtual bool clear() const = 0;
  [[nodiscard]] virtual bool buffer_geometry(Batch& batch) const = 0;
  [[nodiscard]] virtual bool prepare_shader(const Shader& shader, Batch& batch) const = 0;
  [[nodiscard]] virtual uint32_t upload_texture(const cg::Image& image) const = 0;
  [[nodiscard]] virtual bool bind_texture(uint32_t texture_ref) const = 0;
  [[nodiscard]] virtual bool unbind_texture() const = 0;
  [[nodiscard]] virtual bool activate_shader(const Batch& batch) const = 0;
  [[nodiscard]] virtual bool deactivate_shader() const = 0;
  [[nodiscard]] virtual bool set_uniform(const uint32_t shader_ref, const Uniform<float>& uniform) const = 0;
  [[nodiscard]] virtual bool draw(const Batch& batch) const = 0;
};
} // namespace ow::render