set(CURRENT_TARGET owexampleimgui)


find_package(imgui REQUIRED)
find_package(SDL2 REQUIRED)
find_package(glad REQUIRED)

add_subdirectory(imgui/bindings)

file(GLOB ${CURRENT_TARGET}_SRC
     "*.cpp"
)

add_executable(${CURRENT_TARGET} ${${CURRENT_TARGET}_SRC})
target_include_directories(${CURRENT_TARGET} PUBLIC ${PROJECT_SOURCE_DIR}/)
target_include_directories(${CURRENT_TARGET} PUBLIC imgui/bindings)
target_link_libraries(${CURRENT_TARGET} ow imguibindings2 imgui::imgui SDL2::SDL2 glad::glad)
target_compile_definitions(${CURRENT_TARGET} PUBLIC IMGUI_IMPL_OPENGL_LOADER_GLAD)