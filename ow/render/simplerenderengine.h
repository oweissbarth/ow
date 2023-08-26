#pragma once

#include "ow/render/batchingStrategy.h"
#include "ow/render/renderengine.h"


#include <memory>
#include <vector>

namespace ow::render {


class SimpleRenderEngine: public RenderEngine{
    public:
        explicit SimpleRenderEngine(const RenderBackend& backend);
        bool init() override;
        bool register_object(const cg::Object& object) override;
        bool prepare_render() override;
        bool set_uniform(const Uniform<float>& uniform) override;
        bool render(cg::Image& frame, const math::Mat4f& viewMatrix, const math::Mat4f& projectionMatrix, const math::Vec3f& cameraPosition) override;
        bool shutdown() override;

    private:
        std::vector<Batch> m_batches;
        std::shared_ptr<BatchingStrategy> m_batchingStrategy;
        int m_exposure = 0;

};
}