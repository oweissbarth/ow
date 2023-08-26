#include "sdl2_input_handler.h"
#include "camera_controller.h"
#include "ow/interactive/camera_controller.h"
#include <SDL2/SDL_events.h>
#include <iostream>

namespace ow::interaction{



int MyEventFunction(void *userdata, SDL_Event *event) {
    auto handler = static_cast<SDL2InputHandler*>(userdata);
    switch(event->type){
            case SDL_MOUSEMOTION:
                handler->setMousePosition(math::Vec2f(event->motion.x, event->motion.y));
                break;
            // Handle mouse wheel scroll
            case SDL_MOUSEWHEEL:
                handler->setMouseScroll(event->wheel.y);
                break;
            // Handle mouse button press
            case SDL_MOUSEBUTTONDOWN:
                switch(event->button.button){
                    case SDL_BUTTON_LEFT:
                        handler->setMouseButton(MouseButton::LEFT);
                        break;
                    case SDL_BUTTON_RIGHT:
                        handler->setMouseButton(MouseButton::RIGHT);
                        break;
                    case SDL_BUTTON_MIDDLE:
                        handler->setMouseButton(MouseButton::MIDDLE);
                        break;
                    default:
                        handler->setMouseButton(MouseButton::NONE);
                        break;
                }
                break;
            // Handle mouse button release
            case SDL_MOUSEBUTTONUP:
                handler->setMouseButton(MouseButton::NONE);
                break;
    };
    return 0;
}

SDL2InputHandler::SDL2InputHandler(){
    
    SDL_AddEventWatch(MyEventFunction, this);
}


SDL2InputHandler::~SDL2InputHandler(){
    SDL_DelEventWatch(MyEventFunction, nullptr);
}

void SDL2InputHandler::setMousePosition(math::Vec2f pos){
    m_cur_pos = pos;
    for(auto& listener: m_listeners){
        listener->mouseMoveEvent(MouseMoveEvent{pos, m_mouse_button, m_modifier});
    }
}

void SDL2InputHandler::setMouseScroll(float delta){
    for(auto& listener: m_listeners){
        listener->mouseScrollEvent(MouseScrollEvent{delta});
    }
}

void SDL2InputHandler::setMouseButton(MouseButton button){
    m_mouse_button = button;
}



void SDL2InputHandler::register_listener(std::shared_ptr<CameraController> listener){
    m_listeners.push_back(listener);
}

}