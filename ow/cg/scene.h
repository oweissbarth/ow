#pragma once

#include "ow/cg/object.h"
#include "ow/cg/camera.h"
#include <memory>

namespace ow::cg {
class Scene{
public:
    Scene(std::string name);
    void add_object(const std::shared_ptr<Object>& object);
    void add_camera(const std::shared_ptr<Camera>& camera);

    std::vector<std::shared_ptr<Object>>& objects();

private:
    std::string m_name;
    std::vector<std::shared_ptr<Object>> m_objects;
    std::vector<std::shared_ptr<Camera>> m_cameras;

};
}