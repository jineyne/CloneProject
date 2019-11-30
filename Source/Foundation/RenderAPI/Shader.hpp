#pragma once

#include "cpf.hpp"

#include "UniformBuffer.hpp"
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

    /**
     * ���̴��� ����µ� �ʿ��� ������ �����ϴ� ����ü�Դϴ�.
     */
    struct ShaderCreateInfo {
        GpuProgramCreateInfo vertexInfo;    //< Vertex GpuProgram�� ����µ� �ʿ��� �����Դϴ�.
        GpuProgramCreateInfo fragmentInfo;  //< Fragment GpuProgram�� ����µ� �ʿ��� �����Դϴ�.
    };

    class DLL_EXPORT Shader {
    private:
        ShaderCreateInfo mInfo;

        GLuint mProgramId;

    public:
        Shader(const ShaderCreateInfo &info);
        virtual ~Shader();

    public:
        static GLenum GetShaderType(EGpuProgramType type);

    public:
        void bind();

        void setUniformInt1(const String &name, uint32_t data);
        void setUniformMatrix(const String &name, const Matrix4 &data);

        GLuint getProgramId() const { return mProgramId; }
    private:
        /**
         * �־��� ������ ���̴��� �����մϴ�.
         */
        GLuint createGpuProgram(GpuProgramCreateInfo info);
    };
}
