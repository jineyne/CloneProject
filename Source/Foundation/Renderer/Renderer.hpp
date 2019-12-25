#pragma once

#include "cpf.hpp"

#include "RenderAPI/Shader.hpp"

#include "Renderer/Camera.hpp"
#include "Renderer/Renderable.hpp"

#include "Utility/Module.hpp"

namespace cpf {
    class DLL_EXPORT Renderer : public TModule<Renderer> {
    private:
        std::vector<Renderable *> mRegistedRenderableList;
        std::vector<CameraBase *> mRegistedCameraList;

        CameraBase *mMainCamera;

    public:
        void update();

        void notifyRenderableCreated(Renderable *renderable);
        void notifyRenderableUpdated(Renderable *renderable);
        void notifyRenderableRemoved(Renderable *renderable);

        void notifyCameraCreated(CameraBase *camera);
        void notifyCameraChangeMain(CameraBase *camera);
        void notifyCameraRemoved(CameraBase *camera);

        const CameraBase *getMainCamera() const { return mMainCamera; }
    };
}
