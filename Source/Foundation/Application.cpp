#include "Application.hpp"

namespace cpf {
    Application::Application(const ApplicationCreateInfo &info) : mInfo(info), mIsRunning(false) {
    }

    Application::~Application() {
    }

    void Application::runMainLoop() {
        mIsRunning = true;
    }

    void Application::initializeCore() {
    }

    void Application::destroyCore() {
    }
}
