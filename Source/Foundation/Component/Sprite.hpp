#pragma once

#include "cpf.hpp"

#include "RenderAPI/IndexBuffer.hpp"
#include "RenderAPI/Shader.hpp"
#include "RenderAPI/VertexBuffer.hpp"
#include "RenderAPI/VertexDeclaration.hpp"
#include "RenderAPI/Texture.hpp"

#include "Renderer/Renderable.hpp"

#include "Scene/Actor.hpp"
#include "Scene/Component.hpp"

namespace cpf {
    class DLL_EXPORT Sprite : public Component, public Renderable {
    private:
        Texture *mTexture = nullptr;

    public:
        Sprite(Actor *owner);

    public:
        void updateShaderData(Shader *shader) override;

        void setTexture(Texture *texture);
        Texture *getTexture() const { return mTexture; }

    private:
        void onStartUp() override;
        void onShutDown() override;
    };
}
