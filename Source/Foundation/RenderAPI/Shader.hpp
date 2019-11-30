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
     * 쉐이더를 만드는데 필요한 정보를 저장하는 구조체입니다.
     */
    struct ShaderCreateInfo {
        GpuProgramCreateInfo vertexInfo;    //< Vertex GpuProgram을 만드는데 필요한 정보입니다.
        GpuProgramCreateInfo fragmentInfo;  //< Fragment GpuProgram을 만드는데 필요한 정보입니다.
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
         * 주어진 정보로 쉐이더를 생성합니다.
         */
        GLuint createGpuProgram(GpuProgramCreateInfo info);
    };
}
