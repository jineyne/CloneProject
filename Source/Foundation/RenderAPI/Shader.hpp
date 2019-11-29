#pragma once

#include "cpf.hpp"

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

    /**
     * 쉐이더 요소들의 정보를 저장하는 구조체입니다.
     */
    struct SlotInfo {
        String name;
        uint32_t slot;
    };

    class DLL_EXPORT Shader {
    private:
        ShaderCreateInfo mInfo;

        GLenum mProgramId;
        std::unordered_map<EGpuProgramType, SlotInfo> mUniformBlocks;

    public:
        Shader(const ShaderCreateInfo &info);
        virtual ~Shader();

    public:
        static GLenum GetShaderType(EGpuProgramType type);

    public:
        void bind();

    private:
        /**
         * 주어진 정보로 쉐이더를 생성합니다.
         */
        GLuint createGpuProgram(GpuProgramCreateInfo info);
    };
}
