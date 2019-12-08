#include "Application.hpp"

#include "Manager/SceneManager.hpp"

#include "RenderAPI/IndexBuffer.hpp"
#include "RenderAPI/RenderAPI.hpp"
#include "RenderAPI/Shader.hpp"
#include "RenderAPI/VertexBuffer.hpp"
#include "RenderAPI/VertexDataDesc.hpp"
#include "RenderAPI/VertexDeclaration.hpp"

#include "Renderer/Renderable.hpp"

#include "Scene/Component.hpp"
#include "Scene/Scene.hpp"

#include "Debug/Debug.hpp"

using namespace cpf;

class Sprite : public Component, Renderable {
private:
    VertexDeclaration *mVertexDeclaration;
    VertexBuffer *mBuffer;
    IndexBuffer *mIndexBuffer;
    Shader *mShader;

public:
    Sprite(Actor *owner) : Component(owner, "Sprite"), Renderable() {}

public:
    void onStartUp() override {
        ShaderCreateInfo shaderCI{};
        shaderCI.vertexInfo.type = EGpuProgramType::Vertex;
        shaderCI.vertexInfo.source = "#version 330 core\n" "layout (location = 0) in vec3 POSITION;\n" "void main(){\n" " gl_Position = vec4(POSITION.x, POSITION.y, POSITION.z, 1.0);\n }";
        shaderCI.fragmentInfo.type = EGpuProgramType::Fragment;
        shaderCI.fragmentInfo.source = "#version 330 core\n" "out vec4 FragColor;\n" "void main() {\n" "FragColor = vec4(1.0, 0.5, 0.2, 1.0);\n}";
        mShader = Allocator::New<Shader>(shaderCI);

        VertexDataDesc *vdd = Allocator::New<VertexDataDesc>();
        vdd->addElement(VertexElementType::Float3, VertexElementSemantic::Position);
        // vdd->addElement(VertexElementType::Float4, VertexElementSemantic::Color);
        mVertexDeclaration = Allocator::New<VertexDeclaration>(vdd->createElements());

        float vertices[] = {
            0.5f,  0.5f, 0.0f,  // top right
            0.5f, -0.5f, 0.0f,  // bottom right
            -0.5f, -0.5f, 0.0f,  // bottom left
            -0.5f,  0.5f, 0.0f   // top left 
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
        RenderAPI &rapi = RenderAPI::Instance();

        rapi.setVertexDeclaration(mVertexDeclaration);
        rapi.setVertexBuffer(0, {mBuffer});
        rapi.setIndexBuffer(mIndexBuffer);
        rapi.setShader(mShader);

        rapi.drawElements(0, mIndexBuffer->getIndexCount(), 0, mBuffer->getVertexCount(), 0);
    }
};

class SandboxScene : public Scene {
public:
    SandboxScene() : Scene("SandboxScene") {}

protected:
    void onStartUp() override {
        Actor *rectangle = spawnActor<Actor>("rectangle");
        rectangle->addComponenet<Sprite>();
    }

    void onShutDown() override {
        Debug::LogInfo("SandboxScene::ShutDown");
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
