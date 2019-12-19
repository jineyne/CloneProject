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
    class DLL_EXPORT Sprite : public Component, Renderable {
    private:
        VertexDeclaration *mVertexDeclaration = nullptr;
        VertexBuffer *mBuffer = nullptr;
        IndexBuffer *mIndexBuffer = nullptr;
        Shader *mShader = nullptr;
        Texture *mTexture = nullptr;

    public:
        Sprite(Actor *owner);

    public:
        void setTexture(Texture *texture);
        void setShader(Shader *shader);

    private:
        void onStartUp() override;
        void onShutDown() override;
        void render() override;
    };
}
