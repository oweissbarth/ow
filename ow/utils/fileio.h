#pragma once

#include <string>
#include <fstream>
#include <sstream>


namespace ow::utils
{
    std::string read_file(const std::string& path){
        std::ifstream stream(path);

        std::stringstream buffer_v;

        buffer_v << stream.rdbuf();
        return buffer_v.str();
    }
} // namespace ow::utils