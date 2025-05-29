#include "shader.h"
#include "ow/utils/fileio.h"
#include <iostream>

namespace ow::render{
    Shader Shader::from_files(std::vector<std::string> vertex_shader, std::vector<std::string> fragment_shader) {
        std::string vertex_shader_str;
        std::string fragment_shader_str;

        for (const auto& path : vertex_shader) {
            std::cout << "reading vertex shader from " << path << std::endl;
            const auto file_contents = utils::read_file(path);
            if(!file_contents.has_value()){
                std::cout << "failed to read file " << path << std::endl;
                continue;
            }
            vertex_shader_str += file_contents.value() + "\n";
        }

        for (const auto& path : fragment_shader) {
            std::cout << "reading fragment shader from " << path << std::endl;
            const auto file_contents = utils::read_file(path);
            if(!file_contents.has_value()){
                std::cout << "failed to read file " << path << std::endl;
                continue;
            }
            fragment_shader_str += file_contents.value() + "\n";
        }

        return {vertex_shader_str, fragment_shader_str};
    }
}