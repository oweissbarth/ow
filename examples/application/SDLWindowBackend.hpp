#pragma once

#include "WindowBackend.hpp"

#include <SDL2/SDL.h>

#include <vector>
#include <functional>

class SDLWindowBackend : public WindowBackend
{
  public:

    bool initialize_window(int width, int height) override;
    
    void process_events() override;

    void register_event_handler(std::function<void(const SDL_Event&)> handler);

    void swap_buffers() override;
    
    WindowSize get_window_size() override;

    void shutdown() override;
  
  private:
    SDL_Window* m_main_window{};
    SDL_GLContext m_gl_context{};
    bool m_should_quit{false};
    std::vector<std::function<void(const SDL_Event&)>> m_event_handlers;
};
