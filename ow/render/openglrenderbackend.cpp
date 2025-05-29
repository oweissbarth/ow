#include "ow/render/openglrenderbackend.h"
#include "ow/render/shader.h"

#include <cstdint>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cassert>

namespace ow::render {


    void GLAPIENTRY MessageCallback( GLenum source,
                 GLenum type,
                 GLuint id,
                 GLenum severity,
                 GLsizei length,
                 const GLchar* message,
                 const void* userParam )
    {
        if(type == GL_DEBUG_TYPE_ERROR){
            fprintf( stderr, " ** GL ERROR ** type = 0x%x, severity = 0x%x, message = %s\n", type, severity, message);
            assert(false);
        }else{
            //fprintf( stderr, "GL CALLBACK: type = 0x%x, severity = 0x%x, message = %s\n", type, severity, message);
        }
 
    }


    bool OpenGLRenderBackend::init() const
    {
        glEnable              ( GL_DEBUG_OUTPUT );
        glDebugMessageCallback( MessageCallback, nullptr);

        glCullFace(GL_BACK);
        glEnable(GL_CULL_FACE);
        glFrontFace(GL_CCW);
        glEnable (GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);

        glEnable(GL_MULTISAMPLE);

        return true;
    }

    bool OpenGLRenderBackend::setup_viewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height) const{
        glViewport(x,y, width, height);
        return true;
    }

    bool OpenGLRenderBackend::clear() const
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        return true;
    }

    bool OpenGLRenderBackend::buffer_geometry(Batch& batch) const {

        glGenVertexArrays(1, &batch.vao_ref);
        glBindVertexArray(batch.vao_ref);

        GLuint vbo;
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(batch.mesh.vertices.size())*3*sizeof(float), batch.mesh.vertices.data(), GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        // upload normals
        GLuint nbo;
        glGenBuffers(1, &nbo);
        glBindBuffer(GL_ARRAY_BUFFER, nbo);
        glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(batch.mesh.normals.size())*3*sizeof(float), batch.mesh.normals.data(), GL_STATIC_DRAW);

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        if(batch.mesh.uvs.size() > 0){
            GLuint tbo;
            glGenBuffers(1, &tbo);
            glBindBuffer(GL_ARRAY_BUFFER, tbo);
            glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(batch.mesh.uvs.size())*2*sizeof(float), batch.mesh.uvs.data(), GL_STATIC_DRAW);

            glEnableVertexAttribArray(2);
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
        }

        GLuint ebo;
        glGenBuffers(1, &ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLsizeiptr>(batch.mesh.faces.size())*3*sizeof(short), batch.mesh.faces.data(), GL_STATIC_DRAW); 

        glBindVertexArray(0);

        return true;
    }

    bool OpenGLRenderBackend::prepare_shader(const Shader& shader,  Batch& batch) const{

        batch.shader_ref = glCreateProgram();

        GLuint vertID = glCreateShader(GL_VERTEX_SHADER);
        GLuint fragID = glCreateShader(GL_FRAGMENT_SHADER);
        const char* vertexShaderSourceCStr = shader.get_vertex_shader().c_str();
        const char* fragmentShaderSourceCStr = shader.get_fragment_shader().c_str();
        GLint vertexShaderSourceSize = shader.get_vertex_shader().size();
        assert(vertexShaderSourceSize > 0);
        GLint fragmentShaderSourceSize = shader.get_fragment_shader().size();
        assert(fragmentShaderSourceSize > 0);
        glShaderSource(vertID, 1, &vertexShaderSourceCStr, &vertexShaderSourceSize);
        glShaderSource(fragID, 1, &fragmentShaderSourceCStr, &fragmentShaderSourceSize);

        GLint success;
        glCompileShader(vertID);
        glGetShaderiv(vertID, GL_COMPILE_STATUS, &success);
        if(success == 0){
            GLint infoLogLength;
            glGetShaderiv(vertID, GL_INFO_LOG_LENGTH, &infoLogLength);
            std::vector<GLchar> infoLog(infoLogLength);
            glGetShaderInfoLog(vertID, infoLogLength, nullptr, infoLog.data());
            std::cout << "failed to compile vertex shader\n"<<infoLog.data() << std::endl;
            return false;
        }
        glCompileShader(fragID);
        glGetShaderiv(fragID, GL_COMPILE_STATUS, &success);
        if(success == 0){
            GLint infoLogLength;
            glGetShaderiv(fragID, GL_INFO_LOG_LENGTH, &infoLogLength);
            std::vector<GLchar> infoLog(infoLogLength);
            glGetShaderInfoLog(fragID, infoLogLength, nullptr, infoLog.data());
            std::cout << "failed to compile fragment shader:\n"<<infoLog.data() << std::endl;
            return false;
        }


        glAttachShader(batch.shader_ref, vertID);
        glAttachShader(batch.shader_ref, fragID);
        glLinkProgram(batch.shader_ref);
        glGetProgramiv(batch.shader_ref, GL_LINK_STATUS, &success);
        if(success == 0){
            GLint infoLogLength;
            glGetProgramiv(batch.shader_ref, GL_INFO_LOG_LENGTH, &infoLogLength);
            std::vector<GLchar> infoLog(infoLogLength);
            glGetProgramInfoLog(batch.shader_ref, infoLogLength, nullptr, infoLog.data());
            std::cout << "failed to link shader:\n"<< infoLog.data() << std::endl;
            return false;
        }
        return true;
    }

    bool OpenGLRenderBackend::set_uniform(const uint32_t shader_ref, const Uniform<float>& uniform) const{
        GLint viewLoc = glGetUniformLocation(shader_ref, uniform.getName().c_str());
        switch(uniform.getType()){
            case UniformType::FLOAT:
                glUniform1fv(viewLoc, 1, uniform.data());
                break;
            case UniformType::VEC2:
                glUniform2fv(viewLoc, 1, uniform.data());
                break;
            case UniformType::VEC3:
                glUniform3fv(viewLoc, 1, uniform.data());
                break;
            case UniformType::MAT3:
                glUniformMatrix3fv(viewLoc, 1, GL_FALSE, uniform.data());
                break;
            case UniformType::MAT4:
                glUniformMatrix4fv(viewLoc, 1, GL_FALSE, uniform.data());
                break;
            default:
                std::cout << "Unknown uniform type" << std::endl;
                return false;
        }
        return true;
    }

    bool OpenGLRenderBackend::activate_shader(const Batch& batch) const{
        glUseProgram(batch.shader_ref);
        return true;
    }

    bool OpenGLRenderBackend::deactivate_shader() const{
        glUseProgram(0);
        return true;
    }

    uint32_t OpenGLRenderBackend::upload_texture(const cg::Image &image) const{
        GLuint textureID;
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, image.get_width(), image.get_height(), 0, GL_RGB, GL_FLOAT, image.data());
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glGenerateMipmap(GL_TEXTURE_2D);
        return textureID;
    }

    bool OpenGLRenderBackend::bind_texture(uint32_t texture_ref) const{
        glBindTexture(GL_TEXTURE_2D, texture_ref);
        return true;
    }

    bool OpenGLRenderBackend::unbind_texture() const{
        glBindTexture(GL_TEXTURE_2D, 0);
        return true;
    }
    
    bool OpenGLRenderBackend::draw(const Batch& batch) const{
        glBindVertexArray(batch.vao_ref);

        glDrawElements(GL_TRIANGLES, batch.mesh.faces.size()*3, GL_UNSIGNED_SHORT, nullptr);

        glBindVertexArray(0);

        return true;
    }
}
