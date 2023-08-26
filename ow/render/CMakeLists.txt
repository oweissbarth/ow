file(GLOB owrender_SRC
     "*.cpp"
)

find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)


add_library(owrender ${owrender_SRC})
#add_library(owrender OBJECT ${owrender_SRC})
target_include_directories(owrender PUBLIC ${PROJECT_SOURCE_DIR})

target_link_libraries(owrender owcg owmath glad::glad glfw imgui::imgui)