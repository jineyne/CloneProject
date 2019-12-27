#pragma once

#include "cpf.hpp"

namespace cpf {
    enum class BufferUsage {
        Static = 1,
        Dynamic,
        Stream,
        Default = Static,
    };

    class DLL_EXPORT Buffer {
    protected:
        uint32_t mSize = 0;
        BufferUsage mUsage = BufferUsage::Default;
        bool mIsLocked = false;
    
    public:
        Buffer(uint32_t size, BufferUsage usage);
        virtual ~Buffer() = default;

    public:
        virtual void *map(uint32_t offset, uint32_t length) = 0;
        virtual void unmap() = 0;

        virtual GLuint getBufferId() const = 0;
    };
}
