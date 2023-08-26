#include "glfw_input_handler.h"
#include "ow/interactive/camera_controller.h"
#include <GLFW/glfw3.h>

namespace ow::interaction{


GLFWInputHandler::GLFWInputHandler(GLFWwindow* window){
    glfwSetWindowUserPointer(window, this);
    glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods){
        auto* handler= static_cast<interaction::GLFWInputHandler*>(glfwGetWindowUserPointer(window));
        handler->mouse_button_callback(window, button, action, mods);
    });
    glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos){
        auto* handler= static_cast<interaction::GLFWInputHandler*>(glfwGetWindowUserPointer(window));
        handler->mouse_move_callback(window, xpos, ypos);
    });

    glfwSetScrollCallback(window, [](GLFWwindow* window, double xoffset, double yoffset){
        auto* handler= static_cast<interaction::GLFWInputHandler*>(glfwGetWindowUserPointer(window));
        handler->mouse_scroll_callback(window, xoffset, yoffset);
    });
}

void GLFWInputHandler::register_listener(std::shared_ptr<CameraController> listener){
    m_listeners.push_back(listener);
}

void GLFWInputHandler::mouse_button_callback(GLFWwindow* window, int button, int action, int mods){
    if(button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_PRESS){
        m_mouse_button = MouseButton::MIDDLE;
        m_modifier = ModifierKey::NONE;
    }else if(button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_RELEASE){
        m_mouse_button = MouseButton::NONE;
    }
}

void GLFWInputHandler::mouse_move_callback(GLFWwindow* window, double xpos, double ypos){
    m_cur_pos = math::Vec2f(xpos, ypos);
    MouseMoveEvent event{m_cur_pos, m_mouse_button, m_modifier};
    for(auto& listener : m_listeners){
        listener->mouseMoveEvent(event);
    }
}

void GLFWInputHandler::mouse_scroll_callback(GLFWwindow* window, double xoffset, double yoffset){
    MouseScrollEvent event{static_cast<float>(yoffset)};
    for(auto& listener : m_listeners){
        listener->mouseScrollEvent(event);
    }
}

/*

    glfwSetMouseButtonCallback(window.get(), [](GLFWwindow* window, int button, int action, int mods){
        auto* controller= static_cast<interaction::CameraController*>(glfwGetWindowUserPointer(window));
        if(button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_PRESS){
            double xpos, ypos;
            glfwGetCursorPos(window, &xpos, &ypos);
            controller->cursor_pos = glm::vec2(xpos, ypos);
            controller->rotating = true;
        }else if(button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_RELEASE){
            controller->rotating = false;
        }
    });


    glfwSetCursorPosCallback(window.get(), [](GLFWwindow* window, double xpos, double ypos){
        auto* controller = static_cast<interaction::CameraController*>( glfwGetWindowUserPointer( window ));
        controller->(math::Vec2f(xpos, ypos));
        controller->update();
    });
*/

}