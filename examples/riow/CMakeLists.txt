file(GLOB owexampleriow_SRC
     "*.cpp"
)


add_executable(owexampleriow ${owexampleriow_SRC})
target_include_directories(owexampleriow PUBLIC ${PROJECT_SOURCE_DIR}/)
target_link_libraries(owexampleriow ow)