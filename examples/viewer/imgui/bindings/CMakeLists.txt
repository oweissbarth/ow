file(GLOB imguibindings_SRC
     "*.cpp"
)

add_library(imguibindings ${imguibindings_SRC})
target_include_directories(imguibindings PUBLIC ${PROJECT_SOURCE_DIR})
target_link_libraries(imguibindings PUBLIC imgui::imgui SDL2::SDL2 glad::glad)
target_compile_definitions(imguibindings PUBLIC IMGUI_IMPL_OPENGL_LOADER_GLAD)