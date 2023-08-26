file(GLOB owio_SRC
     "*.cpp"
)

file(GLOB owio_PCH
     "*_pch.h"
)



find_package(TinyGLTF CONFIG REQUIRED)

add_library(owio ${owio_SRC})
#add_library(owio OBJECT ${owio_SRC})
target_include_directories(owio PUBLIC ${PROJECT_SOURCE_DIR})
#target_precompile_headers(owio PRIVATE ${owio_PCH})
target_link_libraries(owio PUBLIC owcg TinyGLTF::TinyGLTF)

get_target_property(owio_INCLUDES TinyGLTF::TinyGLTF INTERFACE_INCLUDE_DIRECTORIES)

message(STATUS "Include dirs: ${owio_INCLUDES}")