#include "ow/cg/mesh.h"


#include "ow/cg/pbr_material.h"
#include "tinygltf_pch.h"

#include "gltf.h"
#include "ow/cg/camera.h"
#include "ow/cg/object.h"
#include "ow/cg/scene.h"
#include "ow/math/vec3.h"
#include <cstdint>
#include <memory>



namespace ow::io {

std::shared_ptr<cg::Scene> GLTFLoader::load(const std::string& path){

    tinygltf::Model model;
    tinygltf::TinyGLTF loader;
    std::string err;
    std::string warn;

    

    bool loaded;
    if(path.ends_with(".gltf")) {
        loaded = loader.LoadASCIIFromFile(&model, &err, &warn, path);
    } else if(path.ends_with(".glb")) {
        loaded = loader.LoadBinaryFromFile(&model, &err, &warn, path); // for binary glTF(.glb)
    } else {
        return {};
    }

    if(!loaded) {
        std::cout << err<< std::endl;
        return std::shared_ptr<cg::Scene>{};
    }


    auto gltf_scene = model.scenes[model.defaultScene];

    std::shared_ptr<cg::Scene> scene = std::make_shared<cg::Scene>(gltf_scene.name);


    for(int node_id: gltf_scene.nodes){
        auto node = model.nodes[node_id];
        if(node.camera != -1){
            auto camera = load_camera(node, model);
            scene->add_camera(camera);
            continue;
        }

        if(node.mesh != -1){
            auto object = load_object(node, model);
            scene->add_object(object);
            continue;
        }
    }

    return scene;
}

std::shared_ptr<cg::Camera> GLTFLoader::load_camera(const tinygltf::Node &node, const tinygltf::Model& model){
    auto gltf_cam = model.cameras[node.camera];

    math::Vec3f pos(node.translation[0], node.translation[1], node.translation[2]);
    math::Vec3f lookAt(math::Vec3f(0,0,1));
    math::Vec3f up(0,0,1);

    cg::SensorData sensor;
    cg::LensData lens;

    return std::make_shared<cg::Camera>(pos, lookAt, up, sensor, lens);
}

std::shared_ptr<cg::Object> GLTFLoader::load_object(const tinygltf::Node &node, const tinygltf::Model& model){
    auto gltf_object = model.meshes[node.mesh];

    math::Vec3f pos(0,0,0);
    if(!node.translation.empty()){
        pos = math::Vec3f(node.translation[0], node.translation[1], node.translation[2]);
    }

    std::shared_ptr<cg::Object> object = std::make_shared<cg::Object>();
    object->name = node.name;

    std::vector<std::shared_ptr<cg::Mesh>> meshes;

    for(auto prim: gltf_object.primitives){

        std::vector<math::Vec3f> vertices;
        std::vector<math::Vec3f> normals;
        std::vector<math::Vec3<short>> faces;

        vertices = load_from_buffer<float>(model.accessors[prim.attributes["POSITION"]], model);
        std::cout << "loaded " <<vertices.size() << " vertices"<<std::endl;
        normals = load_from_buffer<float>(model.accessors[prim.attributes["NORMAL"]], model);
        std::cout << "loaded " <<normals.size() << " normals"<<std::endl;
        faces = load_from_buffer<short>(model.accessors[prim.indices], model);
        std::cout << "loaded " <<faces.size() << " faces"<<std::endl;

        std::shared_ptr mesh = std::make_shared<cg::Mesh>();
        mesh->vertices = vertices;
        mesh->normals = normals;
        mesh->faces = faces;

        mesh->material = load_material(model.materials[prim.material]);

        meshes.push_back(mesh);
    }
    object->meshes = meshes;

    return object;
}

template <typename T>
std::vector<math::Vec3<T>> GLTFLoader::load_from_buffer(const tinygltf::Accessor& accessor, const tinygltf::Model &model){
    size_t numberOfElements = accessor.count * 3;
    size_t numberOfVectors = accessor.count;
    if(accessor.type == TINYGLTF_TYPE_SCALAR){
        numberOfElements = accessor.count;
        numberOfVectors = accessor.count / 3;
    }
    std::vector<math::Vec3<T>> data;
    data.reserve(numberOfVectors);

    auto buffer_view = model.bufferViews[accessor.bufferView]; 

    auto buffer = model.buffers[buffer_view.buffer];

    uint8_t* raw_byte_buffer = reinterpret_cast<uint8_t*>(buffer.data.data()) + accessor.byteOffset + buffer_view.byteOffset;

    T* raw_element_buffer = reinterpret_cast<T*>(raw_byte_buffer);

    std::span<T> b = std::span(raw_element_buffer, numberOfElements);
    
    for(auto i = 0; i < numberOfVectors; i++){
        math::Vec3<T> v(b[3*i], b[3*i+1], b[3*i+2]);
        //std::cout << v << std::endl;
        data.push_back(v);
    }
    return data;

}

std::shared_ptr<cg::PBRMaterial> GLTFLoader::load_material(const tinygltf::Material& material){
    auto result = std::make_shared<cg::PBRMaterial>();
    if(material.pbrMetallicRoughness.baseColorFactor.size() == 4){
        auto albedo = material.pbrMetallicRoughness.baseColorFactor;
        result->albedo = {static_cast<float>(albedo[0]), static_cast<float>(albedo[1]), static_cast<float>(albedo[2])};
    }
    result->roughness = material.pbrMetallicRoughness.roughnessFactor;
    result->metallic = material.pbrMetallicRoughness.metallicFactor;
    if(material.emissiveFactor.size() == 3){
        auto emission = material.emissiveFactor;
        result->emissive = {static_cast<float>(emission[0]), static_cast<float>(emission[1]), static_cast<float>(emission[2])};
    }
    return result;
}
}