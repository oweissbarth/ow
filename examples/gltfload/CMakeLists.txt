file(GLOB owexampleloadgltf_SRC
     "*.cpp"
)


add_executable(owexampleloadgltf ${owexampleloadgltf_SRC})
target_include_directories(owexampleloadgltf PUBLIC ${PROJECT_SOURCE_DIR}/)
target_link_libraries(owexampleloadgltf ow)