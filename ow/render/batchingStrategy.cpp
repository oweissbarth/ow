#include "ow/render/batchingStrategy.h"
#include <vector>


namespace ow::render {
void NoBatchingStrategy::add_mesh(const cg::Mesh &mesh){
    m_meshes.push_back(mesh);
}

std::vector<Batch> NoBatchingStrategy::get_batches(){
    std::vector<Batch> batches;
    
    for(const auto& mesh: m_meshes){
        Batch b;
        b.mesh = mesh;
        batches.push_back(b);
    }
    return batches;
}
}