#include "MeshData.hpp"

#include "Debug/Debug.hpp"

namespace cpf {
    MeshData::MeshData(uint32_t vertexCount, uint32_t indexCount, const SPtr<VertexDataDesc> &vertexDesc) 
        : mVertexCount(vertexCount), mIndexCount(indexCount), mVertexDesc(vertexDesc) {
        mVertexData = Allocator::Alloc<uint8_t>(vertexDesc->getVertexStride() * vertexCount);
        mIndexData = Allocator::Alloc<uint8_t>(sizeof(uint32_t) * indexCount);
    }

    MeshData::~MeshData() {}

    void MeshData::addVertexData(void *data, uint32_t size) {
        uint32_t offset = mVertexDesc->getVertexStride();
        if (size % offset != 0) {
            Debug::LogWarning("addVertexData: Invalid size");
            return;
        }

        memcpy(mVertexData, data, size);
    }

    void MeshData::addIndexData(void *data, uint32_t size) {
        uint32_t offset = sizeof(uint32_t);
        if (size % offset != 0) {
            Debug::LogWarning("addIndexData: Invalid size");
            return;
        }

        memcpy(mIndexData, data, size);
    }
}
