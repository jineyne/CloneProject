#include "Application.hpp"

#include "Debug/Debug.hpp"

namespace cpf {

    TMODULE_IMPLEMENT(DLL_EXPORT, Application);

    Application::Application(const ApplicationCreateInfo &info) : mInfo(info), mIsRunning(false) {
    }

    Application::~Application() {
    }

    void Application::runMainLoop() {
        mIsRunning = true;
        auto &app = Application::Instance();
    }

    void Application::onStartUp() {
        initializeCore();
    }

    void Application::onShutDown() {
        destroyCore();
    }

    void Application::initializeCore() {
    }

    void Application::destroyCore() {
    }
}
