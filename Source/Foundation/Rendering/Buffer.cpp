#include "Buffer.hpp"

namespace cpf {
    Buffer::Buffer(uint32_t size, uint32_t count, BufferUsage usage) : mSize(size * count), mUsage(usage) {}
}
