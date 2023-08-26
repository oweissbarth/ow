#include <imgui.h>
#include "imgui/bindings/imgui_impl_sdl2.h"
#include "imgui/bindings/imgui_impl_opengl3.h"

#include <stdio.h>
#include <iostream>

#include <glad/glad.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_syswm.h>

int main()
{
    int screen_width = 640, screen_height = 480;
    SDL_Window * main_window = nullptr;
    SDL_GLContext gl_context = nullptr;
    SDL_Event event = { 0 };
    bool should_quit = false;

    if (SDL_Init(SDL_INIT_EVENTS) < 0) {
            std::cout << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
            return 1;
        }

    // CONFIGURE OPENGL ATTRIBUTES USING SDL:
    int context_flags = SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG;
#ifdef _DEBUG
    context_flags |= SDL_GL_CONTEXT_DEBUG_FLAG;
#endif
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, context_flags);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    // CREATE AND SDL WINDOW CONFIGURED FOR OPENGL:
    if (0 == (main_window = SDL_CreateWindow("OpenGL Init Example", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screen_width, screen_height, SDL_WINDOW_OPENGL))) {
        std::cout <<"Failed to create window: " << SDL_GetError() << std::endl;
        return 1;
    }

    // CREATE THE OPENGL CONTEXT AND MAKE IT CURRENT:
    if(NULL == (gl_context = SDL_GL_CreateContext(main_window))) {
         std::cout << "Failed to create OpenGL context" << std::endl;
         return 1;
    }
    else SDL_GL_MakeCurrent(main_window, gl_context);

    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        std::cout << "Failed to initialize glad" << std::endl;
        return 1;
    }

    SDL_SysWMinfo info;
    SDL_VERSION(&info.version)
    if (SDL_GetWindowWMInfo(main_window,&info)) { 
        if (info.subsystem == SDL_SYSWM_WAYLAND) {
            std::cout << "Wayland detected" << std::endl;
        }else{
            std::cout << "Not Wayland" << std::endl;
        }
    }

    // Initialize ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();

    ImGui_ImplSDL2_InitForOpenGL(main_window, gl_context);
	ImGui_ImplOpenGL3_Init();

   ImGui::StyleColorsDark();

	while (!should_quit)
	{
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);
		while (SDL_PollEvent(&event) != 0) {
            ImGui_ImplSDL2_ProcessEvent(&event);
            switch (event.type) {
            case SDL_QUIT:
                should_quit = true;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                case SDLK_ESCAPE:
                    should_quit = true;
                    break;
                }
                break;
            }
        }

		// feed inputs to dear imgui, start new frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplSDL2_NewFrame();
		ImGui::NewFrame();

		// render your GUI
		ImGui::Begin("Triangle Position/Color");
		ImGui::Button("I am a button");
        ImGui::End();

		// Render dear imgui into screen
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		SDL_GL_SwapWindow(main_window);
	}

	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	SDL_Quit();
	return 0;
}