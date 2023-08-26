#pragma once

#include "ow/render/batch.h"
#include "ow/render/renderingbackend.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <memory>

namespace ow::render {





class OpenGLRenderBackend: public RenderBackend{
public:
    OpenGLRenderBackend() = default;
    //~OpenGLRenderBackend() = default;

    [[nodiscard]] bool init() const override;

    [[nodiscard]] bool setup_viewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height) const override;

    [[nodiscard]] bool clear() const override;

    [[nodiscard]] bool buffer_geometry(Batch& batch) const override;
    [[nodiscard]] bool prepare_shader(Batch& batch) const override;
    [[nodiscard]] bool set_uniform(const uint32_t shader_ref, const Uniform<float>& uniform) const override;
    [[nodiscard]] bool activate_shader(const Batch& batch) const override;
    [[nodiscard]] bool deactivate_shader() const override;
    [[nodiscard]] bool draw(const Batch& batch) const override;

};
}