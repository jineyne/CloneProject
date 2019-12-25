#pragma once

#include "cpf.hpp"

#include "RenderAPI/VertexDataDesc.hpp"

namespace cpf {
    class DLL_EXPORT MeshData {
    private:
        uint32_t mVertexCount;
        uint32_t mIndexCount;

        uint8_t *mVertexData;
        uint8_t *mIndexData;

        SPtr<VertexDataDesc> mVertexDesc;

    public:
        MeshData(uint32_t vertexCount, uint32_t indexCount, const SPtr<VertexDataDesc> &vertexDesc);
        ~MeshData();

    public:
        template <typename T>
        void addVertexData(std::vector<T> data) {
            addVertexData(data.data(), sizeof(T) * data.size());
        }
        void addVertexData(void *data, uint32_t size);

        template <typename T>
        void addIndexData(std::vector<T> data) {
            addIndexData(data.data(), sizeof(T) * data.size());
        }
        void addIndexData(void *data, uint32_t size);

        uint32_t getVertexCount() const { return mVertexCount; }
        uint32_t getIndexCount() const { return mIndexCount; }

        const uint8_t *getVertexData() const { return mVertexData; }
        const uint8_t *getIndexData() const { return mIndexData; }
    };
}
