#pragma once

#include "ow/render/batchingStrategy.h"
#include "ow/render/renderengine.h"


#include <memory>
#include <vector>
#include <optional>

namespace ow::render {


class SimpleRenderEngine: public RenderEngine{
    public:
        explicit SimpleRenderEngine(const RenderBackend& backend);
        bool init() override;
        bool register_object(const cg::Object& object) override;
        bool prepare_render() override;
        bool set_exposure(float exposure);
        bool set_environment_map(const cg::Image& environmentMap);
        bool render(const math::Mat4f& viewMatrix, const math::Mat4f& projectionMatrix, const math::Vec3f& cameraPosition) override;
        bool shutdown() override;

    private:
        std::vector<Batch> m_batches;
        std::shared_ptr<BatchingStrategy> m_batchingStrategy;
        float m_exposure = 0;
        std::optional<uint32_t> m_environmentMapTextureRef;

};
}