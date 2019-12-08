#pragma once

#include "cpf.hpp"

#include "RenderAPI/Buffer.hpp"
#include "RenderAPI/GpuBuffer.hpp"

namespace cpf {
    class DLL_EXPORT IndexBuffer : public Buffer {
    private:
        GpuBuffer *mBuffer = nullptr;
        
        uint32_t mElementSize;
        uint32_t mElementCount;

    public:
        IndexBuffer(uint32_t size, uint32_t count, BufferUsage usage);
        ~IndexBuffer();

    public:
        void initialize();

        void *map(uint32_t offset, uint32_t length) override;
        void unmap() override;

        uint32_t getIndexSize() const { return mElementSize; }
        uint32_t getIndexCount() const { return mElementCount; }

        GLuint getBufferId() const override;
    };
}
