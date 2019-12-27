#pragma once

#include "cpf.hpp"

#include "RenderAPI/Buffer.hpp"

namespace cpf {
    class DLL_EXPORT GpuBuffer : public Buffer {
    private:
        GLuint mBufferId = 0;
        GLenum mBufferType = 0;

        bool mIsZeroLock = false;

    public:
        GpuBuffer(GLenum bufferType, uint32_t size, BufferUsage usage);

        ~GpuBuffer() override;

    public:
        static GLenum GetUsage(BufferUsage usage);

    public:
        void *map(uint32_t offset, uint32_t lenth) override;

        void unmap() override;

        GLuint getBufferId() const override;
    };
}
