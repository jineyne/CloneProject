#include "GpuBuffer.hpp"

#include "Debug/Debug.hpp"

namespace cpf {
    GpuBuffer::GpuBuffer(GLenum bufferType, uint32_t size, uint32_t count, BufferUsage usage) 
        : Buffer(size, count, usage), mBufferType(bufferType) {

        glGenBuffers(1, &mBufferId);
        glBindBuffer(bufferType, mBufferId);
        glBufferData(bufferType, mSize, nullptr, GetUsage(mUsage));
    }

    GpuBuffer::~GpuBuffer() {
        if (mBufferId != 0) {
            glDeleteBuffers(1, &mBufferId);
        }
    }

    GLenum GpuBuffer::GetUsage(BufferUsage usage) {
        switch (usage) {
        case BufferUsage::Static:
        default:
            return GL_STATIC_DRAW;

        case BufferUsage::Dynamic:
            return GL_DYNAMIC_DRAW;

        case BufferUsage::Stream:
            return GL_STREAM_DRAW;
        }
    }

    void *GpuBuffer::map(uint32_t offset, uint32_t length) {
        if (mBufferId == 0) {
            return nullptr;
        }
        
        glBindBuffer(mBufferType, mBufferId);
        GLenum access = GL_MAP_READ_BIT | GL_MAP_WRITE_BIT;

        if (length > 0) {
            void *buffer = glMapBufferRange(mBufferType, offset, length, access);
            if (buffer == nullptr) {
                Debug::LogError("Cannot map opengl buffer!");
            }
            mIsZeroLock = false;

            return buffer;
        } else {
            mIsZeroLock = true;
        }

        return nullptr;
    }

    void GpuBuffer::unmap() {
        if (mBufferId == 0) {
            return;
        }

        glBindBuffer(mBufferType, mBufferId);
        if (!mIsZeroLock) {
            if (!glUnmapBuffer(mBufferType)) {
                Debug::LogError("Buffer data currupted!.please reload");
            }
        }
    }
}
