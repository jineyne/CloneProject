#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "ResourceManager.hpp"

#include "Debug/Debug.hpp"

#include "RenderAPI/Texture.hpp"

namespace cpf {
    template<class T> T *ResourceManager::load(const Path &path) {
        Debug::LogError("{} is not support resource type", TypeOf<T>()->getName());

        return nullptr;
    }

    template<> DLL_EXPORT Texture *ResourceManager::load(const Path &path) {
        auto it = mLoadedResourceList.find(path);
        if (it != mLoadedResourceList.end()) {
            return static_cast<Texture *>(it->second);
        } {
            int width, height, nrChannels;
            unsigned char *buf = stbi_load(path.toString().c_str(), &width, &height, &nrChannels, 0); 

            TextureCreateInfo textureCI{};
            textureCI.width = width;
            textureCI.height = height;
            textureCI.depth = 1;
            textureCI.mipsCount = 1;

            Texture *texture = Allocator::New<Texture>(textureCI);
            texture->write(buf);

            stbi_image_free(buf);

            mLoadedResourceList.insert(std::make_pair(path, texture));

            return texture;
        }
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
