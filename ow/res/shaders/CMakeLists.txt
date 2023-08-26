add_custom_target(copy_resources)


add_custom_command(
    TARGET copy_resources POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/ow/res
            ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/res)