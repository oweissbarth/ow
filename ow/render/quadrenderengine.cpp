#include "ow/render/quadrenderengine.h"
#include "ow/render/batch.h"


namespace ow::render {

QuadRenderEngine::QuadRenderEngine(const RenderBackend& backend): RenderEngine(backend) {}

bool QuadRenderEngine::init(){
    return false;
}

bool QuadRenderEngine::shutdown(){
    return false;
}

bool QuadRenderEngine::prepare_render() {
    auto quad = cg::Mesh::create_quad();
    m_batch.mesh = quad;

    if(!m_backend.buffer_geometry(m_batch)){
        std::cout << "Failed to buffer geometry" << std::endl;
        return false;
    }

    auto shader = render::Shader::from_files({"res/shaders/quad.vert"}, {"res/shaders/quad.frag"});

    if(!m_backend.prepare_shader(shader, m_batch)){
        std::cout << "Failed to prepare shader" << std::endl;
        return false;
    }

    return true;

}

bool QuadRenderEngine::set_image(const cg::Image& image){
    m_texture = m_backend.upload_texture(image);
    return true;
}

bool QuadRenderEngine::register_object(const cg::Object& object) {
    return false;
}

bool QuadRenderEngine::render(const math::Mat4f& viewMatrix, const math::Mat4f& projectionMatrix, const math::Vec3f& cameraPosition){
    if(!m_backend.clear()) [[unlikely]]{
            std::cout << "Failed to clear" << std::endl;
            return false;
        }

        if(!m_backend.activate_shader(m_batch)){
            std::cout << "Failed to activate shader" << std::endl;
            return false;
        }

        if(!m_backend.bind_texture(m_texture)){
            std::cout << "Failed to bind texture" << std::endl;
            return false;
        }


        if(!m_backend.draw(m_batch)) [[unlikely]]{
            std::cout << "Drawing failed" << std::endl;
        }

        if(!m_backend.deactivate_shader()){
            std::cout << "Failed to deactivate shader" << std::endl;
            return false;
        }

        if(!m_backend.unbind_texture()){
            std::cout << "Failed to unbind texture" << std::endl;
            return false;
        }

        return true;
}


}

