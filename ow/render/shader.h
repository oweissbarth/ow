#pragma once

#include <string>
#include <utility>
#include <vector>
namespace ow::render {
    class Shader {
        public:
            Shader(std::string  vertex_shader, std::string  fragment_shader): m_vertex_shader(std::move(vertex_shader)), m_fragment_shader(std::move(fragment_shader)) {}
            [[nodiscard]] const std::string& get_vertex_shader() const { return m_vertex_shader; }
            [[nodiscard]] const std::string& get_fragment_shader() const { return m_fragment_shader; }

            static Shader from_files(std::vector<std::string> vertex_shader, std::vector<std::string> fragment_shader);
        private:
            std::string m_vertex_shader;
            std::string m_fragment_shader;
    };
}