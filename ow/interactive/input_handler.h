#pragma once

#include "camera_controller.h"

#include <memory>

namespace ow::interaction{
    class InputHandler{
        virtual void register_listener(std::shared_ptr<CameraController> listener) = 0;
    };
}