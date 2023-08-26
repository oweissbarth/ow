#pragma once

#include "input_handler.h"
#include "ow/interactive/camera_controller.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <memory>
#include <vector>

namespace ow::interaction{

class GLFWInputHandler: public InputHandler{
    public:

    explicit GLFWInputHandler(GLFWwindow* window);

    void register_listener(std::shared_ptr<CameraController> listener) override;

    void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
    void mouse_move_callback(GLFWwindow* window, double xpos, double ypos);
    void mouse_scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

private:
    math::Vec2f m_cur_pos;
    ModifierKey m_modifier = ModifierKey::NONE;
    MouseButton m_mouse_button = MouseButton::NONE;
    std::vector<std::shared_ptr<CameraController>> m_listeners;
};

}