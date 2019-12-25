#include "ResourceManager.hpp"

#include "Debug/Debug.hpp"

namespace cpf {
    template<class T, typename ...Args> T *ResourceManager::load(Args&&...args) {
        Debug::LogError("{} is not support resource type", TypeOf<T>()->getName());

        return nullptr;
    }

    void ResourceManager::onStartUp() {
        SPtr<VertexDataDesc> vdd = Allocator::MakeShared<VertexDataDesc>();
        vdd->addElement(VertexElementType::Float3, VertexElementSemantic::Position);
        vdd->addElement(VertexElementType::Float2, VertexElementSemantic::TexCoord);

        SPtr<MeshData> meshData = Allocator::MakeShared<MeshData>(4, 6, vdd);
        float vertices[] = {
            0.5f,  0.5f, 0.0f, 1.0f, 1.0f,      // top right
            0.5f, -0.5f, 0.0f, 1.0f, 0.0f,      // bottom right
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,     // bottom left
            -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,     // top left 
        };
        meshData->addVertexData(vertices, sizeof(vertices));

        uint32_t indices[] = {
            0, 1, 2,   // first triangle
            2, 3, 0    // second triangle
        };
        meshData->addIndexData(indices, sizeof(indices));

        MeshCreateInfo spriteMeshCI{};
        spriteMeshCI.name = "SpriteMesh";
        spriteMeshCI.vertexCount = 4;
        spriteMeshCI.indexCount = 6;
        spriteMeshCI.vertexDesc = vdd;
        spriteMeshCI.initialData = meshData;
        mSpriteMesh = Allocator::New<Mesh>(spriteMeshCI);
    }

    void ResourceManager::onShutDown() {
        Allocator::Delete(mSpriteMesh);
    }
}
