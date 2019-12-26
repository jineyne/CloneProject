#include "Sprite.hpp"

#include "Manager/ResourceManager.hpp"

#include "RenderAPI/RenderAPI.hpp"
#include "RenderAPI/VertexDataDesc.hpp"


namespace cpf {
    Sprite::Sprite(Actor *owner) : Component(owner, "Sprite"), Renderable() {}

    void Sprite::setTexture(Texture *texture) {
        mTexture = texture;
    }

    void Sprite::onStartUp() {
        setMesh(ResourceManager::Instance().getSpriteMesh());
    }

    void Sprite::onShutDown() {
    }

    void Sprite::updateShaderData(Shader *shader) {
        shader->setUniformMatrix("cpModel", mOwner->getLocalMatrix());
        shader->setTexture(mTexture);
    }
}
