#pragma once

#include "input_handler.h"
#include "ow/interactive/camera_controller.h"
#include "ow/math/vec2.h"

#include <SDL2/SDL.h>

#include <memory>
#include <vector>

namespace ow::interaction{

class SDL2InputHandler: public InputHandler{
    public:

    explicit SDL2InputHandler();

    ~SDL2InputHandler();

    void register_listener(std::shared_ptr<CameraController> listener) override;

    void setMousePosition(math::Vec2f pos);
    void setMouseScroll(float delta);
    void setMouseButton(MouseButton button);

private:
    math::Vec2f m_cur_pos;
    ModifierKey m_modifier = ModifierKey::NONE;
    MouseButton m_mouse_button = MouseButton::NONE;
    std::vector<std::shared_ptr<CameraController>> m_listeners;
};

}