#pragma once

#include "cpf.hpp"

#include "RenderAPI/Buffer.hpp"
#include "RenderAPI/GpuBuffer.hpp"

namespace cpf {
    class DLL_EXPORT VertexBuffer : public Buffer {
    private:
        GpuBuffer *mBuffer = nullptr;

    public:
        VertexBuffer(uint32_t size, uint32_t count, BufferUsage usage);
        virtual ~VertexBuffer();

    public:
        void initialize();

        void *map(uint32_t offset, uint32_t length) override;
        void unmap() override;

        GLuint getBufferId() const override;
    };
}