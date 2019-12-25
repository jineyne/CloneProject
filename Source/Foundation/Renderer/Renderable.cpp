#include "Renderable.hpp"

#include "Renderer/Renderer.hpp"

namespace cpf {
    Renderable::Renderable() {
        Renderer::Instance().notifyRenderableCreated(this);
    }

    Renderable::~Renderable() {
        Renderer::Instance().notifyRenderableRemoved(this);
    }

    void Renderable::setMesh(Mesh *mesh) {
        mMesh = mesh;
    }

    Mesh *Renderable::getMesh() const {
        return mMesh;
    }

    void Renderable::setShader(Shader *shader) {
        mShader = shader;
    }

    Shader *Renderable::getShader() const { 
        return mShader;
    }
}
