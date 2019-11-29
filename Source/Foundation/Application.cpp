#include "Application.hpp"

#include "Manager/RenderWindowManager.hpp"

#include "Rendering/IndexBuffer.hpp"
#include "Rendering/Shader.hpp"
#include "Rendering/VertexBuffer.hpp"

#include "Debug/Debug.hpp"

namespace cpf {

    TMODULE_IMPLEMENT(DLL_EXPORT, Application);

    void glfwErrorCallback(int error, const char* description) {
        Debug::LogError(description);
    }

    Application::Application(const ApplicationCreateInfo &info) : mInfo(info), mIsRunning(false) {
    }

    Application::~Application() {
    }

    void Application::runMainLoop() {
        mIsRunning = true;

        uint32_t vao = 0;
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        ShaderCreateInfo shaderCI{};
        shaderCI.vertexInfo.type = EGpuProgramType::Vertex;
        shaderCI.vertexInfo.source = "#version 330 core\n" "layout (location = 0) in vec3 aPos;\n" "void main(){\n" " gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n }";
        shaderCI.fragmentInfo.type = EGpuProgramType::Fragment;
	    shaderCI.fragmentInfo.source = "#version 330 core\n" "out vec4 FragColor;\n" "void main() {\n" "FragColor = vec4(1.0, 0.5, 0.2, 1.0);\n}";
        Shader *shader = Allocator::New<Shader>(shaderCI);

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

        float *vbp = static_cast<float *>(vb->map(0, sizeof(vertices)));
        memcpy(vbp, vertices, sizeof(vertices));
        vb->unmap();

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);  

        IndexBuffer *ib = Allocator::New<IndexBuffer>(sizeof(uint32_t), 6, BufferUsage::Default);
        ib->initialize();

        uint32_t *ibp = static_cast<uint32_t *>(ib->map(0, sizeof(indices)));
        memcpy(ibp, indices, sizeof(indices));
        ib->unmap();

        while (mIsRunning) {
            RenderWindowManager::Instance().update();

            glClear(GL_COLOR_BUFFER_BIT);

            shader->bind();
            glBindBuffer(GL_VERTEX_ARRAY, vb->getBufferId());
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib->getBufferId());

            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

            mPrimaryWindow->swapBuffers(0);
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
        if (!glfwInit()) {
            Debug::LogFatal("Failed to initialize glfw!");
        }

        glfwSetErrorCallback(glfwErrorCallback);
        RenderWindowManager::StartUp();

        mPrimaryWindow = RenderWindowManager::Instance().initialize(mInfo.primaryWindowCreateInfo);
    }

    void Application::destroyCore() {
        RenderWindowManager::ShutDown();

        glfwTerminate();
    }
}
