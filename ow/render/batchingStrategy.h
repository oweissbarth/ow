#pragma once

#include "ow/cg/mesh.h"
#include "ow/render/batch.h"


namespace ow::render{

class BatchingStrategy{
    public:
        virtual void add_mesh(const cg::Mesh& mesh) = 0;
        virtual std::vector<Batch> get_batches() = 0;
};

class NoBatchingStrategy: public BatchingStrategy{
    public:
        virtual void add_mesh(const cg::Mesh& mesh) override;
        virtual std::vector<Batch> get_batches() override;
    private:
        std::vector<cg::Mesh> m_meshes;
};

}