#pragma once

#include "ow/cg/object.h"
#include "ow/cg/image.h"
#include "ow/render/renderingbackend.h"
#include "ow/render/uniform.h"
#

namespace ow::render {

class RenderEngine {
public:
  explicit RenderEngine(const RenderBackend& backend): m_backend(backend) {}
  virtual bool init() = 0;
  virtual bool register_object(const cg::Object& object) = 0;
  virtual bool prepare_render() = 0;
  virtual bool set_uniform(const Uniform<float>& uniform) = 0;
  virtual bool render(cg::Image& frame, const math::Mat4f& viewMatrix, const math::Mat4f& projectionMatrix, const math::Vec3f& cameraPosition) = 0;
  virtual bool shutdown() = 0;

protected:
    const RenderBackend& m_backend;
};

} // namespace ow::render