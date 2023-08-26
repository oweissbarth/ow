#pragma once

#include "mesh.h"

#include <string>
#include <memory>
#include <vector>

namespace ow::cg{

struct Object
{
    std::string name;
    std::vector<std::shared_ptr<Mesh>> meshes;
};

}