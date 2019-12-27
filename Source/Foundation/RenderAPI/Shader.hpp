#pragma once

#include "cpf.hpp"

#include "RenderAPI/Texture.hpp"
#include "RenderAPI/UniformBuffer.hpp"
#include "RenderAPI/VertexDeclaration.hpp"

#include "Math/Matrix4.hpp"

namespace cpf {
    enum class EGpuProgramType {
        Vertex,
        Fragment,
    };

    struct GpuProgramCreateInfo {
        EGpuProgramType type;
        String source;
    };

    struct DLL_EXPORT Attribute {
    private:
        String mName;
        VertexElementSemantic mSemantic;

    public:
        Attribute(const String &name, VertexElementSemantic semantic)
            : mName(name), mSemantic(semantic) {}

    public:
        int32_t matchesName(const String &name);
        VertexElementSemantic getSemantic() const { return mSemantic; }
    };

    struct ShaderCreateInfo {
        GpuProgramCreateInfo vertexInfo;
        GpuProgramCreateInfo fragmentInfo;
    };

    class DLL_EXPORT Shader {
    private:
        ShaderCreateInfo mInfo;

        GLuint mProgramId;
        VertexDeclaration * mInputDeclaration;

    public:
        Shader(const ShaderCreateInfo &info);
        virtual ~Shader();

    public:
        static GLenum GetShaderType(EGpuProgramType type);

    public:
        void bind();

        void setUniformInt1(const String &name, uint32_t data);
        void setUniformMatrix(const String &name, const Matrix4 &data);

        void setTexture(const Texture *texture);

        VertexDeclaration *getInputDeclaration() const { return mInputDeclaration; }

        GLuint getProgramId() const { return mProgramId; }

    private:
        GLuint createGpuProgram(GpuProgramCreateInfo info);

        void buildVertexDeclarayion(uint32_t programId);

        bool attribNameToElementSemantic(const String &name, VertexElementSemantic &semantic, uint32_t &index);
        VertexElementType glTypeToAttribType(GLenum glType);
    };
}
