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
    [[nodiscard]] bool prepare_shader(const Shader& shader, Batch& batch) const override;
    [[nodiscard]] bool set_uniform(const uint32_t shader_ref, const Uniform<float>& uniform) const override;
    [[nodiscard]] uint32_t upload_texture(const cg::Image& image) const override;
    [[nodiscard]] bool bind_texture(uint32_t texture_ref) const override;
    [[nodiscard]] bool unbind_texture() const override;
    [[nodiscard]] bool activate_shader(const Batch& batch) const override;
    [[nodiscard]] bool deactivate_shader() const override;
    [[nodiscard]] bool draw(const Batch& batch) const override;

};
}