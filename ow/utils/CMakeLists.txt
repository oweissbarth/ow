file(GLOB owutils_SRC
     "*.cpp"
)


add_library(owutils ${owutils_SRC})
#add_library(owutils OBJECT ${owutils_SRC})
target_include_directories(owutils PUBLIC ${PROJECT_SOURCE_DIR})