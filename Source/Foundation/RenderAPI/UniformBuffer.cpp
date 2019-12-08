#include "UniformBuffer.hpp"

namespace cpf {
    UniformBuffer::UniformBuffer(uint32_t size, uint32_t count, BufferUsage usage)
        : Buffer(size, usage) {}

    UniformBuffer::~UniformBuffer() {
        if (mBuffer) {
            Allocator::Delete(mBuffer);
        }
    }

    void UniformBuffer::initialize() {
        mBuffer = Allocator::New<GpuBuffer>(GL_UNIFORM_BUFFER, mSize, mUsage);
    }

    void *UniformBuffer::map(uint32_t offset, uint32_t length) {
        return mBuffer->map(offset, length);
    }

    void UniformBuffer::unmap() {
        mBuffer->unmap();
    }

    GLuint UniformBuffer::getBufferId() const {
        return mBuffer->getBufferId();
    }
}
