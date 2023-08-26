
#include "ow/render/simplerenderengine.h"
#include "ow/cg/object.h"
#include "ow/cg/mesh.h"
#include "ow/render/batchingStrategy.h"
#include "ow/render/renderengine.h"
#include "ow/render/renderingbackend.h"
#include "simplerenderengine.h"


namespace ow::render {

    SimpleRenderEngine::SimpleRenderEngine(const RenderBackend& backend)
    : RenderEngine(backend)
    , m_batchingStrategy(std::make_shared<NoBatchingStrategy>())
    {

    }


    bool SimpleRenderEngine::init() {
        m_backend.init();
        return true;
    }

    bool SimpleRenderEngine::register_object(const cg::Object& object) {
        for(const auto& mesh_ptr: object.meshes){
            cg::Mesh mesh = *mesh_ptr;
            m_batchingStrategy->add_mesh(mesh);
        }
        return true;
    }

    bool SimpleRenderEngine::prepare_render() {
        m_batches = m_batchingStrategy->get_batches();


        // Buffer geometry
        for(auto& batch: m_batches){
            if(!m_backend.buffer_geometry(batch)){
                std::cout << "Failed to buffer geometry" << std::endl;
                return false;
            }
        }
        std::cout << "Buffered geometry for "<< m_batches.size() << " batches" << std::endl;
        // Setup textures

        // Setup shaders
        for(auto& batch: m_batches){
            if(!m_backend.prepare_shader(batch)){
                std::cout << "Failed to prepare shader" << std::endl;
                return false;
            }
        }
        

        return true;
    }

    bool SimpleRenderEngine::set_uniform(const Uniform<float>& uniform) {
        for(auto& batch: m_batches){
            if(!m_backend.activate_shader(batch)){
                std::cout << "Failed to activate shader" << std::endl;
                return false;
            }

            if(!m_backend.set_uniform(batch.shader_ref, uniform)){
                std::cout << "Failed to set uniform" << std::endl;
                return false;
            }

            if(!m_backend.deactivate_shader()){
                std::cout << "Failed to deactivate shader" << std::endl;
                return false;
            }
        }
        return true;
    }

    bool SimpleRenderEngine::render(cg::Image& frame, const math::Mat4f& viewMatrix, const math::Mat4f& projectionMatrix, const math::Vec3f& cameraPosition) {
        m_backend.clear();

        math::Mat4f modelMatrix = math::Mat4f::identity();
        math::Mat4f modelViewProjectionMatrix = projectionMatrix * viewMatrix * modelMatrix;
        math::Mat3f normalMatrix = (modelMatrix).toMat3().inverse().transpose();

        for(auto& batch: m_batches){
            if(!m_backend.activate_shader(batch)){
                std::cout << "Failed to activate shader" << std::endl;
                return false;
            }
            
            if(!m_backend.set_uniform(batch.shader_ref, Uniform<float>("viewMatrix", viewMatrix))){
                std::cout << "Failed to set viewMatrix uniform" << std::endl;
                return false;
            }
            if(!m_backend.set_uniform(batch.shader_ref, Uniform<float>("modelMatrix", modelMatrix))){
                std::cout << "Failed to set modelMatrix uniform" << std::endl;
                return false;
            }
            if(!m_backend.set_uniform(batch.shader_ref, Uniform<float>("modelViewProjectionMatrix", modelViewProjectionMatrix))){
                std::cout << "Failed to set modelViewProjectionMatrix uniform" << std::endl;
                return false;
            }
            if(!m_backend.set_uniform(batch.shader_ref, Uniform<float>("normalMatrix", normalMatrix))){
                std::cout << "Failed to set normalMatrix uniform" << std::endl;
                return false;
            }
            if(!m_backend.set_uniform(batch.shader_ref, Uniform<float>("cameraPosition", cameraPosition))){
                std::cout << "Failed to set cameraPosition uniform" << std::endl;
                return false;
            }

            if(!m_backend.draw(batch)) [[unlikely]]{
                std::cout << "Drawing failed" << std::endl;
            }

            if(!m_backend.deactivate_shader()){
                std::cout << "Failed to deactivate shader" << std::endl;
                return false;
            }
        }
        return true;
    }

    bool SimpleRenderEngine::shutdown() {
        return true;
    }
}
