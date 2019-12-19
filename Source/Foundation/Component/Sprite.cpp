#include "Sprite.hpp"

#include "RenderAPI/RenderAPI.hpp"
#include "RenderAPI/VertexDataDesc.hpp"

namespace cpf {
    Sprite::Sprite(Actor *owner) : Component(owner, "Sprite"), Renderable() {}

    void Sprite::setTexture(Texture *texture) {
        mTexture = texture;
    }

    void Sprite::setShader(Shader *shader) {
        mShader = shader;
    }

    void Sprite::onStartUp() {
        VertexDataDesc *vdd = Allocator::New<VertexDataDesc>();
        vdd->addElement(VertexElementType::Float3, VertexElementSemantic::Position);
        vdd->addElement(VertexElementType::Float2, VertexElementSemantic::TexCoord);
        // vdd->addElement(VertexElementType::Float4, VertexElementSemantic::Color);
        mVertexDeclaration = Allocator::New<VertexDeclaration>(vdd->createElements());

        float vertices[] = {
            0.5f,  0.5f, 0.0f, 1.0f, 1.0f,      // top right
            0.5f, -0.5f, 0.0f, 1.0f, 0.0f,      // bottom right
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,     // bottom left
            -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,     // top left 
        };
        mBuffer = Allocator::New<VertexBuffer>(vdd->getVertexStride(), 4, BufferUsage::Default);
        mBuffer->initialize();
        float *vbp = static_cast<float *>(mBuffer->map(0, sizeof(vertices)));
        memcpy(vbp, vertices, sizeof(vertices));
        mBuffer->unmap();

        uint32_t indices[] = {
            0, 1, 2,   // first triangle
            2, 3, 0    // second triangle
        };

        mIndexBuffer = Allocator::New<IndexBuffer>(sizeof(uint32_t), 6, BufferUsage::Default);
        mIndexBuffer->initialize();
        uint32_t *ibp = static_cast<uint32_t *>(mIndexBuffer->map(0, sizeof(indices)));
        memcpy(ibp, indices, sizeof(indices));
        mIndexBuffer->unmap();
    }

    void Sprite::onShutDown() {
        Allocator::Delete(mIndexBuffer);
        Allocator::Delete(mBuffer);
        Allocator::Delete(mVertexDeclaration);
    }

    void Sprite::render() {
        if (mTexture == nullptr || mShader == nullptr) {
            return;
        }

        mShader->setUniformMatrix("ModelMVP", mOwner->getLocalMatrix());
        mShader->setTexture(mTexture);
        RenderAPI &rapi = RenderAPI::Instance();

        rapi.setVertexDeclaration(mVertexDeclaration);
        rapi.setVertexBuffer(0, {mBuffer});
        rapi.setIndexBuffer(mIndexBuffer);
        rapi.setShader(mShader);

        rapi.drawElements(0, mIndexBuffer->getIndexCount(), 0, mBuffer->getVertexCount(), 0);
    }
}
