#include "ow/render/openglrenderbackend.h"
#include "ow/math/mat4.h"
#include "ow/math/vec3.h"
#include "ow/utils/fileio.h"

#include <cstddef>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <memory>
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
        return false;
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

        GLuint ebo;
        glGenBuffers(1, &ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLsizeiptr>(batch.mesh.faces.size())*3*sizeof(short), batch.mesh.faces.data(), GL_STATIC_DRAW); 

        glBindVertexArray(0);

        return true;
    }

    bool OpenGLRenderBackend::prepare_shader(Batch& batch) const{
        std::string vertexShaderSource = utils::read_file("res/shaders/simple.vert");

        std::string fragmentShaderSource = utils::read_file("res/shaders/simple.frag");
        std::string fragmentPBRShaderSource = utils::read_file("res/shaders/pbr.glsl");
        fragmentShaderSource =  fragmentShaderSource+fragmentPBRShaderSource;

        batch.shader_ref = glCreateProgram();

        GLuint vertID = glCreateShader(GL_VERTEX_SHADER);
        GLuint fragID = glCreateShader(GL_FRAGMENT_SHADER);
        const char* vertexShaderSourceCStr = vertexShaderSource.c_str();
        const char* fragmentShaderSourceCStr = fragmentShaderSource.c_str();
        GLint vertexShaderSourceSize = vertexShaderSource.size();
        assert(vertexShaderSourceSize > 0);
        GLint fragmentShaderSourceSize = fragmentShaderSource.size();
        assert(fragmentShaderSourceSize > 0);
        glShaderSource(vertID, 1, &vertexShaderSourceCStr, &vertexShaderSourceSize);
        glShaderSource(fragID, 1, &fragmentShaderSourceCStr, &fragmentShaderSourceSize);

        GLint success;
        glCompileShader(vertID);
        glGetShaderiv(vertID, GL_COMPILE_STATUS, &success);
        if(success == 0){
            GLchar infoLog[1024];
            glGetShaderInfoLog(vertID, sizeof(infoLog), nullptr, infoLog);
            std::cout << "failed to compile vertex shader\n"<<infoLog << std::endl;
            return false;
        }
        glCompileShader(fragID);
        glGetShaderiv(fragID, GL_COMPILE_STATUS, &success);
        if(success == 0){
            GLchar infoLog[1024];
            glGetShaderInfoLog(fragID, sizeof(infoLog), nullptr, infoLog);
            std::cout << "failed to compile fragment shader:\n"<<infoLog << std::endl;
            return false;
        }


        glAttachShader(batch.shader_ref, vertID);
        glAttachShader(batch.shader_ref, fragID);
        glLinkProgram(batch.shader_ref);
        glGetProgramiv(batch.shader_ref, GL_LINK_STATUS, &success);
        if(success == 0){
            GLchar infoLog[1024];
            glGetProgramInfoLog(batch.shader_ref, sizeof(infoLog), nullptr, infoLog);
            std::cout << "failed to link shader:\n"<< infoLog << std::endl;
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
    
    bool OpenGLRenderBackend::draw(const Batch& batch) const{
        glBindVertexArray(batch.vao_ref);

        /* Matrices */

        /*math::Mat4f modelMatrix = math::Mat4f::identity();
        math::Mat4f modelViewProjectionMatrix = projectionMatrix * viewMatrix * modelMatrix;
        math::Mat3f normalMatrix = (modelMatrix).toMat3().inverse().transpose();

        GLint viewLoc = glGetUniformLocation(batch.shader_ref, "viewMatrix");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, viewMatrix.data());

        GLint modelLoc = glGetUniformLocation(batch.shader_ref, "modelMatrix");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, modelMatrix.data());

        GLint modelViewProjectionLoc = glGetUniformLocation(batch.shader_ref, "modelViewProjectionMatrix");
        glUniformMatrix4fv(modelViewProjectionLoc, 1, GL_FALSE, modelViewProjectionMatrix.data());

        GLint normalLoc = glGetUniformLocation(batch.shader_ref, "normalMatrix");
        glUniformMatrix3fv(normalLoc,1, GL_FALSE, normalMatrix.data());

        GLint cameraLoc = glGetUniformLocation(batch.shader_ref, "cameraPosition");
        glUniform3f(cameraLoc, cameraPosition.x, cameraPosition.y, cameraPosition.z);*/

        /* Material */

        GLint albedoLoc = glGetUniformLocation(batch.shader_ref, "albedo");
        glUniform3f(albedoLoc, batch.mesh.material->albedo.r, batch.mesh.material->albedo.g, batch.mesh.material->albedo.b);
        GLint roughnessLoc = glGetUniformLocation(batch.shader_ref, "roughness");
        glUniform1f(roughnessLoc, batch.mesh.material->roughness);
        GLint metallicLoc = glGetUniformLocation(batch.shader_ref, "metallic");
        glUniform1f(metallicLoc, batch.mesh.material->metallic);
        GLint emissionLoc = glGetUniformLocation(batch.shader_ref, "emission");
        glUniform3f(emissionLoc, batch.mesh.material->emissive.r, batch.mesh.material->emissive.g, batch.mesh.material->emissive.b);

        glDrawElements(GL_TRIANGLES, batch.mesh.faces.size()*3, GL_UNSIGNED_SHORT, nullptr);

        glBindVertexArray(0);
        glUseProgram(0);

        return true;
    }
}