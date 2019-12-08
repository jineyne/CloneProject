#include "VertexBuffer.hpp"

namespace cpf {
    VertexBuffer::VertexBuffer(uint32_t size, uint32_t count, BufferUsage usage)
        : Buffer(size * count, usage), mElementSize(size), mElementCount(count) {}

    VertexBuffer::~VertexBuffer() {
        if (mBuffer) {
            Allocator::Delete(mBuffer);
        }
    }

    void VertexBuffer::initialize() {
        mBuffer = Allocator::New<GpuBuffer>(GL_ARRAY_BUFFER, mSize, mUsage);
    }

    void *VertexBuffer::map(uint32_t offset, uint32_t length) {
        return mBuffer->map(offset, length);
    }

    void VertexBuffer::unmap() {
        mBuffer->unmap();
    }

    GLuint VertexBuffer::getBufferId() const {
        return mBuffer->getBufferId();
    }
}
