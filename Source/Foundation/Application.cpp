#include "Application.hpp"

#include "Manager/RenderWindowManager.hpp"

#include "RenderAPI/IndexBuffer.hpp"
#include "RenderAPI/RenderAPI.hpp"
#include "RenderAPI/Shader.hpp"
#include "RenderAPI/VertexBuffer.hpp"

#include "Debug/Debug.hpp"

namespace cpf {
    TMODULE_IMPLEMENT(DLL_EXPORT, Application);

    Application::Application(const ApplicationCreateInfo &info) : mInfo(info), mIsRunning(false) {
    }

    Application::~Application() {
    }

    void Application::runMainLoop() {
        mIsRunning = true;

        auto &rapi = RenderAPI::Instance();
        rapi.setRenderTarget(mPrimaryWindow.get());

        uint32_t vao = 0;
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        ShaderCreateInfo shaderCI{};
        shaderCI.vertexInfo.type = EGpuProgramType::Vertex;
        shaderCI.vertexInfo.source = "#version 330 core\n" "layout (location = 0) in vec3 aPos;\n" "void main(){\n" " gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n }";
        shaderCI.fragmentInfo.type = EGpuProgramType::Fragment;
	    shaderCI.fragmentInfo.source = "#version 330 core\n" "out vec4 FragColor;\n" "void main() {\n" "FragColor = vec4(1.0, 0.5, 0.2, 1.0);\n}";
        Shader *shader = Allocator::New<Shader>(shaderCI);
        rapi.setShader(shader);

        float vertices[] = {
            0.5f,  0.5f, 0.0f,  // top right
            0.5f, -0.5f, 0.0f,  // bottom right
            -0.5f, -0.5f, 0.0f,  // bottom left
            -0.5f,  0.5f, 0.0f   // top left 
        };  

        uint32_t indices[] = {
            0, 1, 2,   // first triangle
            2, 3, 0    // second triangle
        };

        VertexBuffer *vb = Allocator::New<VertexBuffer>(sizeof(float), 12, BufferUsage::Default);
        vb->initialize();
        rapi.setVertexBuffer(0, {vb});

        float *vbp = static_cast<float *>(vb->map(0, sizeof(vertices)));
        memcpy(vbp, vertices, sizeof(vertices));
        vb->unmap();

        IndexBuffer *ib = Allocator::New<IndexBuffer>(sizeof(uint32_t), 6, BufferUsage::Default);
        ib->initialize();
        rapi.setIndexBuffer(ib);

        uint32_t *ibp = static_cast<uint32_t *>(ib->map(0, sizeof(indices)));
        memcpy(ibp, indices, sizeof(indices));
        ib->unmap();

        while (mIsRunning) {
            RenderWindowManager::Instance().update();

            rapi.clearRenderTarget();
            rapi.drawElements(0, ib->getCount(), 0, vb->getCount(), 0);
            rapi.swapBuffers();
        }

        Allocator::Delete(ib);
        Allocator::Delete(vb);
        Allocator::Delete(shader);
    }

    void Application::stopMainLoop() {
        mIsRunning = false;
    }

    void Application::quitRequest() {
        stopMainLoop();
    }

    void Application::onStartUp() {
        initializeCore();
    }

    void Application::onShutDown() {
        destroyCore();
    }

    void Application::initializeCore() {
        RenderAPI::StartUp();
        RenderWindowManager::StartUp();

        mPrimaryWindow = RenderWindowManager::Instance().initialize(mInfo.primaryWindowCreateInfo);
    }

    void Application::destroyCore() {
        RenderWindowManager::ShutDown();
        RenderAPI::ShutDown();
    }
}
