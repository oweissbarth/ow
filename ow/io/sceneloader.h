#pragma once

#include <string>
#include <memory>

#include "ow/cg/scene.h"

/*namespace cg{
    class Scene;
}*/

namespace ow::io {
class SceneLoader{
     static std::shared_ptr<cg::Scene> load(std::string path);
};
}