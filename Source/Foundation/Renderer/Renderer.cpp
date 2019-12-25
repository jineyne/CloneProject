#include "Renderer.hpp"

#include "RenderAPI/RenderAPI.hpp"
#include "Application.hpp"

namespace cpf {
    void Renderer::update() {
        RenderAPI &rapi = RenderAPI::Instance();
        rapi.setRenderTarget(Application::Instance().getPrimaryWindow().get());
        rapi.clearRenderTarget();


        for (auto *renderable : mRegistedRenderableList) {
            Mesh *mesh = renderable->getMesh();
            Shader *shader = renderable->getShader();

            renderable->updateShaderData(shader);

            rapi.setShader(shader);
            rapi.setVertexDeclaration(mesh->getVertexDeclaration());

            rapi.setVertexBuffer(0, {mesh->getVertexBuffer()});
            rapi.setIndexBuffer(mesh->getIndexBuffer());

            rapi.drawElements(0, mesh->getIndexCount(), 0, mesh->getVertexCount(), 0);
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
