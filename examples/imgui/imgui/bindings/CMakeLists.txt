file(GLOB imguibindings_SRC
     "*.cpp"
)

add_library(imguibindings2 ${imguibindings_SRC})
target_include_directories(imguibindings2 PUBLIC ${PROJECT_SOURCE_DIR})
target_link_libraries(imguibindings2 PUBLIC imgui::imgui SDL2::SDL2 glad::glad)
target_compile_definitions(imguibindings2 PUBLIC IMGUI_IMPL_OPENGL_LOADER_GLAD)