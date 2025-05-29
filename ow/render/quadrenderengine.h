#pragma once

#include "ow/render/renderengine.h"
#include "ow/render/renderingbackend.h"
#include "ow/cg/image.h"


#include <memory>
#include <sys/types.h>
#include <vector>
#include <optional>

namespace ow::render {


class QuadRenderEngine: public RenderEngine{
    public:
        explicit QuadRenderEngine(const RenderBackend& backend);
        bool init() override;
        bool register_object(const cg::Object& object) override;
        bool prepare_render() override;
        bool render(const math::Mat4f& viewMatrix, const math::Mat4f& projectionMatrix, const math::Vec3f& cameraPosition) override;
        bool shutdown() override;

        bool set_image(const cg::Image& image);

    private:
        Batch m_batch;
        uint32_t m_texture;
    };
}