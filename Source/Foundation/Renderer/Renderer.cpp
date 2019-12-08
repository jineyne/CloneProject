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
        mRegistedRenderable.push_back(renderable);
    }

    void Renderer::notifyRenderableRemoved(Renderable *renderable) {
        auto it = std::find(mRegistedRenderable.begin(), mRegistedRenderable.end(), renderable);
        if (it != mRegistedRenderable.end()) {
            mRegistedRenderable.erase(it);
        }
    }
}
