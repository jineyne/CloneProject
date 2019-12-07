#pragma once

#include "cpf.hpp"

#include "Renderer/Renderable.hpp"

#include "Utility/Module.hpp"

namespace cpf {
    class DLL_EXPORT Renderer : public TModule<Renderer> {
    private:
        std::vector<Renderable *> mRegistedRenderable;

    public:
        void update();

        void notifyRenderableCreated(Renderable *renderable);
        void notifyRenderableUpdated(Renderable *renderable);
        void notifyRenderableRemoved(Renderable *renderable);
    };
}
