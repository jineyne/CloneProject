#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "Application.hpp"

#include "FileSystem/FileSystem.hpp"

#include "Manager/SceneManager.hpp"

#include "Math/Matrix4.hpp"


#include "RenderAPI/SamplerState.hpp"
#include "RenderAPI/IndexBuffer.hpp"
#include "RenderAPI/RenderAPI.hpp"
#include "RenderAPI/Shader.hpp"
#include "RenderAPI/Texture.hpp"
#include "RenderAPI/VertexBuffer.hpp"
#include "RenderAPI/VertexDataDesc.hpp"
#include "RenderAPI/VertexDeclaration.hpp"

#include "Renderer/Renderable.hpp"

#include "Scene/Component.hpp"
#include "Scene/Scene.hpp"

#include "Debug/Debug.hpp"

using namespace cpf;

String loadFile(const Path &path) {
    auto file = FileSystem::OpenFile(path);
    size_t size = file->size();
    std::vector<char> str(size + 1);

    file->read(str.data(), size);
    str[size] = '\0';
    String result(str.data());

    return result;
}

class Sprite : public Component, Renderable {
private:
    VertexDeclaration *mVertexDeclaration = nullptr;
    VertexBuffer *mBuffer = nullptr;
    IndexBuffer *mIndexBuffer = nullptr;
    Shader *mShader = nullptr;
    Texture *mTexture = nullptr;

public:
    Sprite(Actor *owner) : Component(owner, "Sprite"), Renderable() {}

public:
    void setTexture(Texture *texture) {
        mTexture = texture;
    }
    void onStartUp() override {
        ShaderCreateInfo shaderCI{};

        shaderCI.vertexInfo.type = EGpuProgramType::Vertex;
        shaderCI.vertexInfo.source = loadFile(Path("Assets/Shader/sprite.vert"));

        shaderCI.fragmentInfo.type = EGpuProgramType::Fragment;
        shaderCI.fragmentInfo.source = loadFile(Path("Assets/Shader/sprite.frag"));
        
        mShader = Allocator::New<Shader>(shaderCI);

        VertexDataDesc *vdd = Allocator::New<VertexDataDesc>();
        vdd->addElement(VertexElementType::Float3, VertexElementSemantic::Position);
        vdd->addElement(VertexElementType::Float2, VertexElementSemantic::TexCoord);
        // vdd->addElement(VertexElementType::Float4, VertexElementSemantic::Color);
        mVertexDeclaration = Allocator::New<VertexDeclaration>(vdd->createElements());

        float vertices[] = {
            0.5f,  0.5f, 0.0f, 1.0f, 1.0f,      // top right
            0.5f, -0.5f, 0.0f, 1.0f, 0.0f,      // bottom right
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,     // bottom left
            -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,     // top left 
        };
        mBuffer = Allocator::New<VertexBuffer>(vdd->getVertexStride(), 4, BufferUsage::Default);
        mBuffer->initialize();
        float *vbp = static_cast<float *>(mBuffer->map(0, sizeof(vertices)));
        memcpy(vbp, vertices, sizeof(vertices));
        mBuffer->unmap();

        uint32_t indices[] = {
            0, 1, 2,   // first triangle
            2, 3, 0    // second triangle
        };

        mIndexBuffer = Allocator::New<IndexBuffer>(sizeof(uint32_t), 6, BufferUsage::Default);
        mIndexBuffer->initialize();
        uint32_t *ibp = static_cast<uint32_t *>(mIndexBuffer->map(0, sizeof(indices)));
        memcpy(ibp, indices, sizeof(indices));
        mIndexBuffer->unmap();
    }

    void onShutDown() override {
        Allocator::Delete(mIndexBuffer);
        Allocator::Delete(mBuffer);
        Allocator::Delete(mVertexDeclaration);
    }

    void render() override {
        mShader->setUniformMatrix("ModelMVP", mOwner->getLocalMatrix());
        if (mTexture) {
            mShader->setTexture(mTexture);
        }
        RenderAPI &rapi = RenderAPI::Instance();

        rapi.setVertexDeclaration(mVertexDeclaration);
        rapi.setVertexBuffer(0, {mBuffer});
        rapi.setIndexBuffer(mIndexBuffer);
        rapi.setShader(mShader);

        rapi.drawElements(0, mIndexBuffer->getIndexCount(), 0, mBuffer->getVertexCount(), 0);
    }
};

class SandboxScene : public Scene {
private:
    Actor *rectangle;
    Texture *mGlobalTexture;

public:
    SandboxScene() : Scene("SandboxScene") {}

protected:
    void onStartUp() override {
        int width, height, nrChannels;
        unsigned char *buf = stbi_load("Assets/Image/wall.jpg", &width, &height, &nrChannels, 0); 

        TextureCreateInfo textureCI{};
        textureCI.width = width;
        textureCI.height = height;
        textureCI.depth = 1;
        textureCI.mipsCount = 1;

        mGlobalTexture = Allocator::New<Texture>(textureCI);
        mGlobalTexture->write(buf);

        stbi_image_free(buf);

        rectangle = spawnActor<Actor>("rectangle");
        Sprite *sprite = rectangle->addComponenet<Sprite>();
        sprite->setTexture(mGlobalTexture);
    }

    void onShutDown() override {
        Debug::LogInfo("SandboxScene::ShutDown");
    }

    void onUpdate() override {
        // rectangle->move(Vector3(0.01f, 0.0f, 0.0f));
    }
};

int main() {
    ApplicationCreateInfo appCI{};
    appCI.primaryWindowCreateInfo.width = 1280;
    appCI.primaryWindowCreateInfo.height = 720;
    appCI.primaryWindowCreateInfo.title = "Sandbox";
    appCI.primaryWindowCreateInfo.fullscreen = false;

    Application::StartUp(appCI);

    SceneManager::Instance().createScene<SandboxScene>();

    Application::Instance().runMainLoop();
    Application::ShutDown();

    return 0;
}
