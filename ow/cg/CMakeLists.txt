file(GLOB owcg_SRC
     "*.cpp"
)


add_library(owcg ${owcg_SRC})
#add_library(owcg OBJECT ${owcg_SRC})
target_include_directories(owcg PUBLIC ${PROJECT_SOURCE_DIR})

target_link_libraries(owcg owmath)