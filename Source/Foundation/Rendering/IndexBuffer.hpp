#pragma once

#include "cpf.hpp"

#include "Rendering/Buffer.hpp"
#include "Rendering/GpuBuffer.hpp"

namespace cpf {
    class DLL_EXPORT IndexBuffer : public Buffer {
    private:
        GpuBuffer *mBuffer = nullptr;

    public:
        IndexBuffer(uint32_t size, uint32_t count, BufferUsage usage);
        ~IndexBuffer();

    public:
        void initialize();

        void *map(uint32_t offset, uint32_t length) override;
        void unmap() override;

        GLuint getBufferId() const override;
    };
}
