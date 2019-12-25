#include "Renderer.hpp"

#include "RenderAPI/RenderAPI.hpp"
#include "Application.hpp"

namespace cpf {
    void Renderer::update() {
        RenderAPI &rapi = RenderAPI::Instance();
        rapi.setRenderTarget(Application::Instance().getPrimaryWindow().get());
        rapi.clearRenderTarget();

        for (auto *renderable : mRegistedRenderable) {
            renderable->render();
        }

        rapi.swapBuffers();
    }

    void Renderer::notifyRenderableCreated(Renderable *renderable) {
        mRegistedRenderableList.push_back(renderable);
    }

    void Renderer::notifyRenderableRemoved(Renderable *renderable) {
        auto it = std::find(mRegistedRenderableList.begin(), mRegistedRenderableList.end(), renderable);
        if (it != mRegistedRenderableList.end()) {
            mRegistedRenderableList.erase(it);
        }
    }

    void Renderer::notifyCameraCreated(CameraBase *camera) {
        mRegistedCameraList.push_back(camera);
    }
    
    void Renderer::notifyCameraChangeMain(CameraBase *camera) {
        if (mMainCamera != camera) {
            mMainCamera = camera;
        }
    }

    void Renderer::notifyCameraRemoved(CameraBase *camera) {
        auto it = std::find(mRegistedCameraList.begin(), mRegistedCameraList.end(), camera);
        if (it != mRegistedCameraList.end()) {
            mRegistedCameraList.erase(it);
        }
    }
}
