#include "ow/cg/image.h"
#include "ow/cg/mesh.h"
#include "ow/cg/object.h"
#include "ow/interactive/camera_controller.h"
#include "ow/interactive/sdl2_input_handler.h"
#include "ow/io/gltf.h"
#include "ow/io/imageloader.h"
#include "ow/math/utils.h"
#include "ow/math/vec3.h"
#include "ow/render/openglrenderbackend.h"
#include "ow/render/simplerenderengine.h"

#include "examples/application/SDLWindowBackend.hpp"

#include <GL/gl.h>
#include <iostream>
#include <memory>


#include <imgui.h>
#include "imgui/bindings/imgui_impl_sdl2.h"
#include "imgui/bindings/imgui_impl_opengl3.h"


#include <glad/glad.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_syswm.h>


using namespace ow;



    bool init_imgui(){
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();

        if(!ImGui_ImplSDL2_InitForOpenGL(m_main_window, m_gl_context)){
            std::cout << "Failed to init imgui"<< std:: endl;
            return false;
        }
        if(!ImGui_ImplOpenGL3_Init()){
            std::cout << "Failed to init imgui"<< std:: endl;
            return false;
        }
        ImGui::StyleColorsDark();
        return true;
    }
    static void shutdown_imgui(){
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        ImGui::DestroyContext();
    }


int main(int argc, char** argv)
{
    if(argc != 3){
        std::cout << "Usage: " << argv[0] <<" <path> <environment>" << std::endl;
        return 1;
    }

    auto app = SDLWindowBackend;

    constexpr int screen_width = 640;
    constexpr int screen_height = 480;

    if(!app.intialize_window(screen_width, screen_height)){
        std::cout << "Failed to initialize window" << std::endl;
        return 1;
    }

    auto scene = io::GLTFLoader::load(std::string(argv[1]));

    const render::OpenGLRenderBackend backend{};
    render::SimpleRenderEngine engine(backend);

    for(const auto& object: scene->objects()){
        engine.register_object(*object);
    }

    auto environmentMap = io::ImageLoader::load(std::string(argv[2]));
    if(!engine.set_environment_map(environmentMap)){
        std::cout << "failed to set environment map" << std::endl;
        return 1;
    }

    if(!engine.prepare_render()){
        std::cout << "failed to prepare rendering "<< std:: endl;
        return 1;
    }

    int width;
    int height;
    app.get_window_size(width, height);
    if(!backend.setup_viewport(0, 0, width, height)){
        std::cout << "Failed to setup viewport" << std::endl;
        return 1;
    }

    float aspect_ratio = static_cast<float>(width) / static_cast<float>(height);
    constexpr float fov_degrees = 45.0F;
    float fov_radians = math::radians(fov_degrees);

    if(!app.init_imgui()){
        std::cout << "Failed to init imgui"<< std:: endl;
        return 1;
    }
    
    constexpr float near_plane = 0.1F;
    constexpr float far_plane = 100.F;
    math::Mat4f viewMatrix  = math::Mat4f::identity();
    math::Mat4f projectionMatrix = math::Mat4f::perspective(fov_radians, aspect_ratio, near_plane, far_plane);
    auto controller = std::make_shared<interaction::TurntableCameraController>();

    interaction::SDL2InputHandler input_handler{};

    input_handler.register_listener(controller);

    float exposure = 0.F;
    bool should_quit = false;
    while (!should_quit)
    {
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);
        app.process_events();
        app.process_imgui_events();
        should_quit = app.should_quit();

        // feed inputs to dear imgui, start new frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        interaction::View view = controller->view();

        viewMatrix = view.toMat4();
        auto invViewMatrix = viewMatrix.inverse();
        math::Vec3f camPos{};
        camPos.x = invViewMatrix(3, 0);
        camPos.y = invViewMatrix(3, 1);
        camPos.z = invViewMatrix(3, 2);

        engine.set_exposure(exposure);

        engine.render(viewMatrix, projectionMatrix, camPos);

        // render your GUI
        ImGui::Begin("Demo window");
        ImGui::SliderFloat("Exposure", &exposure, -10, 10);
        ImGui::End();

        // Render dear imgui into screen
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        app.swap_buffers();
    }

    app.shutdown_imgui();
    app.shutdown();

    return 0;
}
