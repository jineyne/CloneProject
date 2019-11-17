#include "Application.hpp"

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

        while (mIsRunning) {
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
        if (!glfwInit()) {
            Debug::LogFatal("Failed to initialize glfw!");
        }

        glfwSetErrorCallback(glfwErrorCallback);
    }

    void Application::destroyCore() {

        glfwTerminate();
    }
}
