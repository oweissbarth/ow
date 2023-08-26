#include "scene.h"
#include <memory>


namespace ow::cg {

    Scene::Scene(std::string name):m_name(std::move(name)){};
    
    void Scene::add_camera(const std::shared_ptr<Camera>& camera){
        m_cameras.emplace_back(camera);
    }

    void Scene::add_object(const std::shared_ptr<Object>& object){
        m_objects.emplace_back(object);
    }

    std::vector<std::shared_ptr<Object>>& Scene::objects()
    {
        return m_objects;
    }


}