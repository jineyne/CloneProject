#include "Buffer.hpp"

namespace cpf {
    Buffer::Buffer(uint32_t size, BufferUsage usage) 
        : mSize(size), mUsage(usage) {}
}
