#include "Scene.hpp"

namespace cpf {
    Scene::Scene(const String &name) : mSceneName(name) {
        mRootActor = Allocator::New<Actor>("RootActor");
    }

    Scene::~Scene() {
        Allocator::Delete(mRootActor);
    }

    void Scene::startUp() {
        onStartUp();
        mRootActor->startUp();
    }

    void Scene::shutDown() {
        onShutDown();
        mRootActor->shutDown();
    }

    void Scene::update() {
        onUpdate();
        mRootActor->update();
    }
}
