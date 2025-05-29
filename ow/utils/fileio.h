#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <optional>
#include <iostream>


namespace ow::utils
{
    std::optional<std::string> read_file(const std::filesystem::path& rel_path){
        #ifdef __linux__
        const auto path = std::filesystem::canonical("/proc/self/exe").parent_path() / rel_path;
        #else
        #error "unsupported platform"
        #endif

        if(!std::filesystem::exists(path)){
            std::cout << "file " << path << " does not exist" << std::endl;
            return {};
        }

        std::ifstream stream(path);

        std::stringstream buffer_v;

        buffer_v << stream.rdbuf();
        return buffer_v.str();
    }
} // namespace ow::utils