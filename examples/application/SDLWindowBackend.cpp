#include "SDLWindowBackend.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_syswm.h>
#include <glad/glad.h>

#include <iostream>


bool SDLWindowBackend::initialize_window(int width, int height){
        if (SDL_Init(SDL_INIT_EVENTS) < 0) {
            std::cout << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
            return false;
        }

        // CONFIGURE OPENGL ATTRIBUTES USING SDL:
        int context_flags = SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG;
    #ifdef _DEBUG
        context_flags |= SDL_GL_CONTEXT_DEBUG_FLAG;
    #endif
        const int BUFFER_SIZE_COLOR = 8;
        const int BUFFER_SIZE_DEPTH = 24;
        const int BUFFER_SIZE_STENCIL = 8;
        const int OPENGL_VERSION_MAJOR = 4;
        const int OPENGL_VERSION_MINOR = 6;

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, context_flags);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, OPENGL_VERSION_MAJOR);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, OPENGL_VERSION_MINOR);
        SDL_GL_SetAttribute(SDL_GL_RED_SIZE, BUFFER_SIZE_COLOR);
        SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, BUFFER_SIZE_COLOR);
        SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, BUFFER_SIZE_COLOR);
        SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, BUFFER_SIZE_COLOR);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, BUFFER_SIZE_DEPTH);
        SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, BUFFER_SIZE_STENCIL);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

        // CREATE AND SDL WINDOW CONFIGURED FOR OPENGL:
        m_main_window = SDL_CreateWindow("OpenGL Init Example", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
        if (m_main_window == nullptr) {
            std::cout <<"Failed to create window: " << SDL_GetError() << std::endl;
            return false;
        }

        // CREATE THE OPENGL CONTEXT AND MAKE IT CURRENT:
        m_gl_context = SDL_GL_CreateContext(m_main_window);
        if(m_gl_context == nullptr) {
            std::cout << "Failed to create OpenGL context" << std::endl;
            return false;
        }
        
        SDL_GL_MakeCurrent(m_main_window, m_gl_context);

        if (gladLoadGLLoader(static_cast<GLADloadproc>(SDL_GL_GetProcAddress)) == 0) {
            std::cout << "Failed to initialize glad" << std::endl;
            return false;
        }

        SDL_SysWMinfo info;
        SDL_VERSION(&info.version)
        if (SDL_GetWindowWMInfo(m_main_window,&info) != 0U) {
            if (info.subsystem == SDL_SYSWM_WAYLAND) {
                std::cout << "Wayland detected" << std::endl;
            }else{
                std::cout << "Not Wayland" << std::endl;
            }
        }
        return true;
    }

void SDLWindowBackend::process_events(){
        SDL_Event event;
        while (SDL_PollEvent(&event) != 0) {
          for (auto& handler : m_event_handlers) {
            handler(event);
          }
          switch (event.type) {
                case SDL_QUIT:
                    m_should_quit = false;
                    break;
                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_ESCAPE) {
                        m_should_quit = true;
                    }
                    break;
                default:
                    break;
            }
        }
    }

void SDLWindowBackend::register_event_handler(std::function<void(const SDL_Event&)> handler){
  m_event_handlers.push_back(std::move(handler));
}

void SDLWindowBackend::swap_buffers(){
        SDL_GL_SwapWindow(m_main_window);
    }

WindowBackend::WindowSize SDLWindowBackend::get_window_size(){
        WindowBackend::WindowSize size;
        SDL_GetWindowSize(m_main_window, &size.width, &size.height);
        return size;
    }

void SDLWindowBackend::shutdown(){
        SDL_GL_DeleteContext(m_gl_context);
        SDL_DestroyWindow(m_main_window);
        SDL_Quit();
}
