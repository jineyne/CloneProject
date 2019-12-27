#include "Application.hpp"

#include "Manager/ResourceManager.hpp"

#include "Component/Sprite.hpp"
#include "Component/Camera.hpp"

#include "FileSystem/FileSystem.hpp"

#include "Manager/SceneManager.hpp"

#include "Math/Matrix4.hpp"
#include "Scene/Scene.hpp"

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

class SandboxScene : public Scene {
private:
    Actor *rectangle;
    Actor *mMainCamera;

    Texture *mTexture;
    Shader *mShader;

public:
    SandboxScene() : Scene("SandboxScene") {}

protected:
    void onStartUp() override {
        ShaderCreateInfo shaderCI{};
        shaderCI.vertexInfo.type = EGpuProgramType::Vertex;
        shaderCI.vertexInfo.source = loadFile(Path("Assets/Shader/sprite.vert"));
        shaderCI.fragmentInfo.type = EGpuProgramType::Fragment;
        shaderCI.fragmentInfo.source = loadFile(Path("Assets/Shader/sprite.frag"));
        mShader = Allocator::New<Shader>(shaderCI);

        rectangle = spawnActor<Actor>("rectangle");
        rectangle->move(Vector3(640, 360, 0));
        rectangle->scale(Vector3(10, 10, 1));
        Sprite *sprite = rectangle->addComponent<Sprite>();
        sprite->setTexture(ResourceManager::Instance().load<Texture>(Path("Assets/Image/wall.jpg")));
        sprite->setShader(mShader);

        mMainCamera = spawnActor<Actor>("main camera");
        mMainCamera->move(Vector3(0, 0, -10));
        Camera *camera = mMainCamera->addComponent<Camera>();
        camera->setProjectionType(EProjectionType::Orthograhic);
        camera->setNear(0.0f);
        camera->setFar(500.0f);
        camera->setAspect(1280.0f / 720.0f);
        camera->setOrthoHeight(720);
        camera->setMain(true);
    }

    void onShutDown() override {
        Debug::LogInfo("SandboxScene::ShutDown");
    }

    void onUpdate() override {
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
