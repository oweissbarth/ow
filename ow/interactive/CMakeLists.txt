file(GLOB owinteractive_SRC
     "*.cpp"
)


add_library(owinteractive ${owinteractive_SRC})
target_include_directories(owinteractive PUBLIC ${PROJECT_SOURCE_DIR})
target_link_libraries(owinteractive owmath glfw)
