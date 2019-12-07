#include "Renderable.hpp"

#include "Renderer/Renderer.hpp"

namespace cpf {
    Renderable::Renderable() {
        Renderer::Instance().notifyRenderableCreated(this);
    }

    Renderable::~Renderable() {
        Renderer::Instance().notifyRenderableRemoved(this);
    }
}
