#pragma once

#include "cpf.hpp"

#include "Mesh/MeshData.hpp"

#include "RenderAPI/IndexBuffer.hpp"
#include "RenderAPI/VertexBuffer.hpp"
#include "RenderAPI/VertexDeclaration.hpp"

#include "Resource/Resource.hpp"

namespace cpf {
    struct MeshCreateInfo {
        String name;

        uint32_t vertexCount;
        uint32_t indexCount;

        SPtr<VertexDataDesc> vertexDesc;
        SPtr<MeshData> initialData;
    };

    class DLL_EXPORT Mesh : public Resource {
    private:
        VertexBuffer *mVertexBuffer;
        IndexBuffer *mIndexBuffer;
        VertexDeclaration *mVertexDeclaration;

    public:
        Mesh(const MeshCreateInfo &info);
        ~Mesh();

    public:
        void write(const SPtr<MeshData> &data);

        VertexBuffer *getVertexBuffer() const;
        IndexBuffer *getIndexBuffer() const;

        uint32_t getVertexCount() const;
        uint32_t getIndexCount() const;

        VertexDeclaration *getVertexDeclaration() const { return mVertexDeclaration; }
    };
}
