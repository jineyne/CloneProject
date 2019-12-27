#pragma once

#include "cpf.hpp"

#include "RenderAPI/IndexBuffer.hpp"
#include "RenderAPI/RenderTarget.hpp"
#include "RenderAPI/Shader.hpp"
#include "RenderAPI/VertexBuffer.hpp"
#include "RenderAPI/VertexDeclaration.hpp"

#include "Utility/Module.hpp"

namespace cpf {
    class DLL_EXPORT RenderAPI : public TModule<RenderAPI> {
    private:
        bool mDrawCallInProgress = false;

        RenderTarget *mActiveRenderTarget = nullptr;
        std::array<VertexBuffer *, 32> mActiveVertexBuffers {nullptr, };
        IndexBuffer *mActiveIndexBuffer = nullptr;
        Shader *mActiveShader = nullptr;
        VertexDeclaration *mVertexDeclaration = nullptr;

    public:
        RenderAPI() = default;
        ~RenderAPI() = default;

    public:
        void beginDraw();

        void endDraw();

        void setRenderTarget(RenderTarget *target);

        void setVertexBuffer(uint32_t index, std::vector<VertexBuffer *> buffers);
        void setIndexBuffer(IndexBuffer *buffer);

        void setShader(Shader *shader);

        void setVertexDeclaration(VertexDeclaration *decl);

        void drawElements(uint32_t indexOffset, uint32_t indexCount, uint32_t vertexOffset, uint32_t vertexCount, 
                uint32_t instanceCount = 0);

        void clearRenderTarget();
        void swapBuffers();

    protected:
        void onStartUp() override;
        void onShutDown() override;
    };
}
