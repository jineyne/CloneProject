#include "SceneManager.hpp"

namespace cpf {
    void SceneManager::loadScene(Scene *scene) {
        unloadScene();

        mActiveScene = scene;
        mDirtyFlags.set(ESceneDirtyFlags::SceneChanged);
    }

    void SceneManager::update() {
        if (mActiveScene == nullptr) {
            return;
        }

        if (mDirtyFlags.isSet(ESceneDirtyFlags::SceneChanged)) {
            mActiveScene->startUp();
            mDirtyFlags.unSet(ESceneDirtyFlags::SceneChanged);
        }

        mActiveScene->update();
    }

    void SceneManager::onShutDown() {
        unloadScene();
    }

    void SceneManager::unloadScene() {
        if (mActiveScene != nullptr) {
            Allocator::Delete(mActiveScene);
        }
    }
}
