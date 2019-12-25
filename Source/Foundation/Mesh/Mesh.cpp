#include "Mesh.hpp"

namespace cpf {
    Mesh::Mesh(const MeshCreateInfo &info) : Resource() {
        setName(info.name);

        mVertexBuffer = Allocator::New<VertexBuffer>(info.vertexDesc->getVertexStride(), info.vertexCount, BufferUsage::Default);
        mVertexBuffer->initialize();

        mIndexBuffer = Allocator::New<IndexBuffer>(sizeof(uint32_t), info.indexCount, BufferUsage::Default);
        mIndexBuffer->initialize();

        mVertexDeclaration = Allocator::New<VertexDeclaration>(info.vertexDesc->createElements());

        if (info.initialData != nullptr) {
            write(info.initialData);
        }
    }

    Mesh::~Mesh() {
        Allocator::Delete(mVertexDeclaration);
        Allocator::Delete(mIndexBuffer);
        Allocator::Delete(mVertexBuffer);
    }

    void Mesh::write(const SPtr<MeshData> &data) {
        uint32_t verticesSize = mVertexBuffer->getVertexSize() * data->getVertexCount();
        float *vbp = static_cast<float *>(mVertexBuffer->map(0, verticesSize));
        memcpy(vbp, data->getVertexData(), verticesSize);
        mVertexBuffer->unmap();

        uint32_t indicesSize = mIndexBuffer->getIndexSize() * data->getIndexCount();
        uint32_t *ibp = static_cast<uint32_t *>(mIndexBuffer->map(0, indicesSize));
        memcpy(ibp, data->getIndexData(), indicesSize);
        mIndexBuffer->unmap();
    }

    VertexBuffer *Mesh::getVertexBuffer() const {
        return mVertexBuffer;
    }

    IndexBuffer *Mesh::getIndexBuffer() const {
        return mIndexBuffer;
    }

    uint32_t Mesh::getVertexCount() const {
        return mVertexBuffer->getVertexCount();
    }

    uint32_t Mesh::getIndexCount() const {
        return mIndexBuffer->getIndexCount();
    }
}
