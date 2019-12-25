#include "Application.hpp"

#include "Manager/ObjectManager.hpp"
#include "Manager/RenderWindowManager.hpp"
#include "Manager/ResourceManager.hpp"
#include "Manager/SceneManager.hpp"
#include "Manager/VertexArrayManager.hpp"

#include "RenderAPI/IndexBuffer.hpp"
#include "RenderAPI/RenderAPI.hpp"
#include "RenderAPI/Shader.hpp"
#include "RenderAPI/VertexBuffer.hpp"

#include "Renderer/Renderer.hpp"

#include "Debug/Debug.hpp"

namespace cpf {
    TMODULE_IMPLEMENT(DLL_EXPORT, Application);

    Application::Application(const ApplicationCreateInfo &info) : mInfo(info), mIsRunning(false) {
    }

    Application::~Application() {
    }

    void Application::runMainLoop() {
        mIsRunning = true;

        while (mIsRunning) {
            RenderWindowManager::Instance().update();
            SceneManager::Instance().update();

            Renderer::Instance().update();
        }
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

        ObjectManager::StartUp();

        Renderer::StartUp();
        VertexArrayManager::StartUp();

        ResourceManager::StartUp();

        SceneManager::StartUp();
    }

    void Application::destroyCore() {
        SceneManager::ShutDown();

        ResourceManager::ShutDown();

        VertexArrayManager::ShutDown();
        Renderer::ShutDown();

        ObjectManager::ShutDown();

        RenderWindowManager::ShutDown();
        RenderAPI::ShutDown();
    }
}
