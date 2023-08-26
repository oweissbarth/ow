find_package(Catch2 3 REQUIRED)
find_package(glm REQUIRED)

add_executable(owtest mat3_test.cpp mat4_test.cpp quaternion_test.cpp turntable_controller_test.cpp glm_test.cpp)
target_include_directories(owtest PUBLIC ${PROJECT_SOURCE_DIR})
target_link_libraries(owtest PRIVATE Catch2::Catch2WithMain glm::glm owmath)