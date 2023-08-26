#include_directories(.)

find_package(glad REQUIRED)



set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_subdirectory(math)
add_subdirectory(utils)
add_subdirectory(cg)
add_subdirectory(io)
add_subdirectory(render)
add_subdirectory(interactive)
add_subdirectory(test)

add_subdirectory(res/shaders)

add_library(ow INTERFACE)
#add_library(ow SHARED $<TARGET_OBJECTS:owutils>   $<TARGET_OBJECTS:owmath> $<TARGET_OBJECTS:owcg> $<TARGET_OBJECTS:owio>)
target_link_libraries(ow INTERFACE owutils owmath owcg owio owrender owinteractive imguibindings)
add_dependencies(ow copy_resources)

