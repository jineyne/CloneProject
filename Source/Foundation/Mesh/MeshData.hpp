#pragma once

#include "cpf.hpp"

#include "RenderAPI/VertexDataDesc.hpp"

namespace cpf {
    class DLL_EXPORT MeshData {
    private:
        uint32_t mVertexCount;
        uint32_t mIndexCount;

        int8_t *mVertexData;
        int8_t *mIndexData;

        VertexDataDesc *mVertexDesc;

    public:
        MeshData(uint32_t vertexCount, uint32_t indexCount, VertexDataDesc *vertexDesc);
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
    };
}
