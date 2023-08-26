#pragma once

#include "ow/cg/pbr_material.h"
#include "ow/io/sceneloader.h"

namespace tinygltf {
    struct Node;
    struct Model;
    struct Accessor;
    struct Material;
}

namespace ow::cg {
    class Camera;
    class Object;
}

namespace ow::io {
class GLTFLoader: public SceneLoader
{
public:
    static std::shared_ptr<cg::Scene> load(const std::string& path); 

private:
    static std::shared_ptr<cg::Camera> load_camera(const tinygltf::Node &node, const tinygltf::Model& model);
    static std::shared_ptr<cg::Object> load_object(const tinygltf::Node &node, const tinygltf::Model& model);
    template <typename T>
    static std::vector<math::Vec3<T>> load_from_buffer(const tinygltf::Accessor& accessor, const tinygltf::Model &model);

    static std::shared_ptr<cg::PBRMaterial> load_material(const tinygltf::Material& material);


};
}