#include "Application.hpp"
#include "Debug/Debug.hpp"

using namespace cpf;

int main() {
    ApplicationCreateInfo appCI{};
    appCI.primaryWindowCreateInfo.width = 1280;
    appCI.primaryWindowCreateInfo.height = 720;
    appCI.primaryWindowCreateInfo.title = "Sandbox";
    appCI.primaryWindowCreateInfo.fullscreen = false;
    Application::StartUp(appCI);
    Application::Instance().runMainLoop();
    Application::ShutDown();

    return 0;
}
