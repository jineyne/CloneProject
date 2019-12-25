#include "Shader.hpp"

#include "Debug/Debug.hpp"

namespace cpf {
    int32_t Attribute::matchesName(const String &name) {
        if (name.length() >= mName.length()) {
            if (name.substr(0, mName.length()) == mName) {
                String indexStr = name.substr(mName.length(), name.length());
                std::stringstream ss(indexStr.c_str());
                uint32_t idx = 0;
                ss >> idx;
                return idx;
            }
        }

        return -1;
    }

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

        buildVertexDeclarayion(mProgramId);

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

    void Shader::setTexture(const Texture *texture) {
        glBindTexture(GL_TEXTURE_2D, texture->getTextureId());
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

    void Shader::buildVertexDeclarayion(uint32_t programId) {
        int32_t attribCount = 0;
        glGetProgramiv(programId, GL_ACTIVE_ATTRIBUTES, &attribCount);

        int32_t maxNameSize = 0;
        glGetProgramiv(programId, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &maxNameSize);

        std::vector<char> attribName(maxNameSize);
        std::vector<VertexElement> elementList;

        for (int32_t i = 0; i < attribCount; i++) {
            int32_t attribSize = 0;
            GLenum attribType = 0;
            glGetActiveAttrib(programId, i, maxNameSize, nullptr, &attribSize, &attribType, attribName.data());

            StringStream ss;
            ss << attribName.data();

            VertexElementSemantic semantic = VertexElementSemantic::Position;
            uint32_t index;
            if (attribNameToElementSemantic(ss.str(), semantic, index)) {
                VertexElementType type = glTypeToAttribType(attribType);
                uint32_t slot = glGetAttribLocation(programId, attribName.data());

                elementList.emplace_back(slot, type, semantic, index);
            }
        }

        mInputDeclaration = Allocator::New<VertexDeclaration>(elementList);
    }

    bool Shader::attribNameToElementSemantic(const String &name, VertexElementSemantic &semantic, uint32_t &index) {
        Attribute attrib[] {
            Attribute("cpf_position", VertexElementSemantic::Position),
            Attribute("cpf_color", VertexElementSemantic::Color),
            Attribute("cpf_texcoord", VertexElementSemantic::TexCoord),
            Attribute("POSITION", VertexElementSemantic::Position),
            Attribute("COLOR", VertexElementSemantic::Color),
            Attribute("TEXCOORD", VertexElementSemantic::TexCoord),
        };

        static const uint32_t attribCount = sizeof(attrib) / sizeof(attrib[0]);

        for (uint32_t i = 0; i < attribCount; i++) {
            int32_t attribIndex = attrib[i].matchesName(name);
            if (attribIndex != -1) {
                index = attribIndex;
                semantic = attrib[i].getSemantic();
                return true;
            }
        }

        return false;
    }

    VertexElementType Shader::glTypeToAttribType(GLenum glType) {
        switch (glType) {
        case GL_FLOAT:
            return VertexElementType::Float1;
        case GL_FLOAT_VEC2:
            return VertexElementType::Float2;
        case GL_FLOAT_VEC3:
            return VertexElementType::Float3;
        case GL_FLOAT_VEC4:
            return VertexElementType::Float4;
        default:
            Debug::LogError("Unsupported vertex attribute type.");
        }

        return VertexElementType::Unknown;
    }
}
