#include "ow/cg/image.h"
#include "ow/cg/mesh.h"
#include "ow/cg/object.h"
#include "ow/interactive/camera_controller.h"
#include "ow/interactive/sdl2_input_handler.h"
#include "ow/io/gltf.h"
#include "ow/math/utils.h"
#include "ow/math/vec3.h"
#include "ow/render/openglrenderbackend.h"
#include "ow/render/simplerenderengine.h"


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


int main(int argc, char** argv)
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
    
    SDL_GL_MakeCurrent(main_window, gl_context);

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

    auto scene = io::GLTFLoader::load(std::string(argv[1]));

    const render::OpenGLRenderBackend backend{};

    cg::Image frame(400,400);

    render::SimpleRenderEngine engine(backend);
    

    //engine.init();
   cg::Object quad {};
    std::shared_ptr<cg::Mesh> mesh = std::make_shared<cg::Mesh>();
    mesh->vertices = {
    math::Vec3f( 0.5F,  0.5F, 0.0F),  // top right
    math::Vec3f( 0.5F, -0.5F, 0.0F),  // bottom right
    math::Vec3f(-0.5F, -0.5F, 0.0F),  // bottom left
    math::Vec3f(-0.5F,  0.5F, 0.0F)  // top left 
    };
    mesh->faces = {  // note that we start from 0!
        math::Vec3s(0, 1, 3),   // first triangle
        math::Vec3s(1, 2, 3)   // second triangle
    };

    mesh->normals = {
        math::Vec3f(0, 0, 1),
        math::Vec3f(0, 0, 1),
        math::Vec3f(0, 0, 1),
        math::Vec3f(0, 0, 1),
        math::Vec3f(0, 0, 1),
        math::Vec3f(0, 0, 1),
    };

    quad.meshes = {std::shared_ptr<cg::Mesh>(mesh)};
    //engine.register_object(quad);
    for(const auto& object: scene->objects()){
        engine.register_object(*object);
        std::cout << "added object" << std::endl;
    }
    

    if(!engine.prepare_render()){
        std::cout << "failed to prepare rendering "<< std:: endl;
        return 1;
    }
    std::cout << "engine initialized" << std::endl;


    int width;
    int height;
    SDL_GL_GetDrawableSize(main_window, &width, &height);
    backend.setup_viewport(0, 0, width, height);

    float aspect_ratio = static_cast<float>(width) / static_cast<float>(height);
    float fov_radians = math::radians(45.0F);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();

    if(!ImGui_ImplSDL2_InitForOpenGL(main_window, gl_context)){
        std::cout << "Failed to init imgui"<< std:: endl;
        return 1;
    }
    if(!ImGui_ImplOpenGL3_Init()){
        std::cout << "Failed to init imgui"<< std:: endl;
        return 1;
    }
    ImGui::StyleColorsDark();

    math::Mat4f viewMatrix  = math::Mat4f::identity();
    math::Mat4f projectionMatrix = math::Mat4f::perspective(fov_radians, aspect_ratio, 0.1F, 100.F);
    auto controller = std::make_shared<interaction::TurntableCameraController>();

    interaction::SDL2InputHandler input_handler{};

    input_handler.register_listener(controller);

    float exposure = 0.F;

    while (!should_quit)
	{
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);
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

        interaction::View view = controller->view();

        viewMatrix = view.toMat4();
        auto invViewMatrix = viewMatrix.inverse();
        math::Vec3f camPos{};
        camPos.x = invViewMatrix(3, 0);
        camPos.y = invViewMatrix(3, 1);
        camPos.z = invViewMatrix(3, 2);
        engine.render(frame, viewMatrix, projectionMatrix, camPos);

        // render your GUI
        ImGui::Begin("Demo window");
        ImGui::SliderFloat("Exposure", &exposure, -10, 10);
        ImGui::End();
        engine.set_uniform({"exposure", exposure});

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