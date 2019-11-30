#include "Shader.hpp"

#include "Debug/Debug.hpp"

namespace cpf {
    Shader::Shader(const ShaderCreateInfo &info) : mInfo(info) {
        GLuint vert = createGpuProgram(info.vertexInfo);
        GLuint frag = createGpuProgram(info.fragmentInfo);

        mProgramId = glCreateProgram();
        glAttachShader(mProgramId, vert);
        glAttachShader(mProgramId, frag);
        glLinkProgram(mProgramId);

        int success;
        char infoLog[512];
        glGetProgramiv(mProgramId, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(mProgramId, 512, nullptr, infoLog);
            Debug::LogError("Failed to link shader.\n{}", infoLog);
        }

        glDeleteShader(vert);
        glDeleteShader(frag);
    }

    Shader::~Shader() {
        glDeleteProgram(mProgramId);
    }

    GLenum Shader::GetShaderType(EGpuProgramType type) {
        switch (type) {
        default:
        case EGpuProgramType::Vertex:
            return GL_VERTEX_SHADER;

        case EGpuProgramType::Fragment:
            return GL_FRAGMENT_SHADER;
        }
    }

    void Shader::bind() {
        glUseProgram(mProgramId);
    }

    void Shader::setUniformInt1(const String &name, uint32_t data) {
        uint32_t index = glGetUniformLocation(mProgramId, name.c_str());
        if (index != -1) {
            glProgramUniform1iv(mProgramId, index, 1, reinterpret_cast<GLint *>(data));
        }
    }

    void Shader::setUniformMatrix(const String &name, const Matrix4 &data) {
        uint32_t index = glGetUniformLocation(mProgramId, name.c_str());
        if (index != -1) {
            glProgramUniformMatrix4fv(mProgramId, index, 1, GL_FALSE, reinterpret_cast<GLfloat *>(&data[0][0]));
        }
    }

    GLuint Shader::createGpuProgram(GpuProgramCreateInfo info) {
        GLuint id = glCreateShader(GetShaderType(info.type));
        const char *src = info.source.c_str();
        glShaderSource(id, 1, &src, nullptr);
        glCompileShader(id);

        int success;
        char infoLog[512];
        glGetShaderiv(id, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(id, 512, nullptr, infoLog);
            Debug::LogError("Failed to compile shader \n{}", infoLog);
            return -1;
        }

        return id;
    }

}
