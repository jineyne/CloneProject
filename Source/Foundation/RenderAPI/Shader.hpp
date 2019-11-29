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
     * ���̴��� ����µ� �ʿ��� ������ �����ϴ� ����ü�Դϴ�.
     */
    struct ShaderCreateInfo {
        GpuProgramCreateInfo vertexInfo;    //< Vertex GpuProgram�� ����µ� �ʿ��� �����Դϴ�.
        GpuProgramCreateInfo fragmentInfo;  //< Fragment GpuProgram�� ����µ� �ʿ��� �����Դϴ�.
    };

    /**
     * ���̴� ��ҵ��� ������ �����ϴ� ����ü�Դϴ�.
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
         * �־��� ������ ���̴��� �����մϴ�.
         */
        GLuint createGpuProgram(GpuProgramCreateInfo info);
    };
}
