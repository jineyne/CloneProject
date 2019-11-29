#include "IndexBuffer.hpp"

namespace cpf {
    IndexBuffer::IndexBuffer(uint32_t size, uint32_t count, BufferUsage usage) 
        : Buffer(size, count, usage) {}

    IndexBuffer::~IndexBuffer() {
        if (mBuffer != nullptr) {
            Allocator::Delete(mBuffer);
        }
    }

    void IndexBuffer::initialize() {
        mBuffer = Allocator::New<GpuBuffer>(GL_ELEMENT_ARRAY_BUFFER, mElementSize, mElementCount, mUsage);
    }

    void *IndexBuffer::map(uint32_t offset, uint32_t length) {
        return mBuffer->map(offset, length);
    }

    void IndexBuffer::unmap() {
        mBuffer->unmap();
    }

    GLuint IndexBuffer::getBufferId() const {
        return mBuffer->getBufferId();
    }
}
