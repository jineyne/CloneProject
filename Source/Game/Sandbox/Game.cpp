#include "Application.hpp"

#include "Manager/SceneManager.hpp"
#include "Scene/Scene.hpp"

#include "Debug/Debug.hpp"

using namespace cpf;

class SandboxScene : public Scene {
public:
    SandboxScene() : Scene("SandboxScene") {}

protected:
    void onStartUp() override {
        Debug::LogInfo("SandboxScene::StartUp");
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
