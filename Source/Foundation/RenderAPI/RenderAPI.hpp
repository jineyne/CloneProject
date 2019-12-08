#pragma once

#include "cpf.hpp"

#include "RenderAPI/IndexBuffer.hpp"
#include "RenderAPI/RenderTarget.hpp"
#include "RenderAPI/Shader.hpp"
#include "RenderAPI/VertexBuffer.hpp"
#include "RenderAPI/VertexDeclaration.hpp"

#include "Utility/Module.hpp"

namespace cpf {
    /**
     * Render 관련한 API입니다.
     */
    class DLL_EXPORT RenderAPI : public TModule<RenderAPI> {
    private:
        bool mDrawCallInProgress = false;

        RenderTarget *mActiveRenderTarget = nullptr;
        std::array<VertexBuffer *, 32> mActiveVertexBuffers {nullptr, };
        IndexBuffer *mActiveIndexBuffer = nullptr;
        Shader *mActiveShader = nullptr;
        VertexDeclaration *mVertexDeclarayion = nullptr;

    public:
        RenderAPI() = default;
        ~RenderAPI() = default;

    public:
        /**
         * 화면에 그리기 전 수행해야 할 것들을 처리합니다.
         */
        void beginDraw();

        /**
         * 화면에 그리기가 끝난 후 수행해야 할 것들을 처리합니다.
         */
        void endDraw();

        /**
         * 그리는 대상을 설정합니다.
         */
        void setRenderTarget(RenderTarget *target);

        /**
         * VertexBuffer를 설정합니다.
         */
        void setVertexBuffer(uint32_t index, std::vector<VertexBuffer *> buffers);
        void setIndexBuffer(IndexBuffer *buffer);

        /**
         * @NOTE:
         *  GraphicPipeline으로 대체될 예정입니다.
         */
        void setShader(Shader *shader);

        void setVertexDeclaration(VertexDeclaration *decl);

        /**
         * 주어진 정보로 배열 데이터에서 그립니다.
         */
        void drawElements(uint32_t indexOffset, uint32_t indexCount, uint32_t vertexOffset, uint32_t vertexCount, 
                uint32_t instanceCount = 0);

        /**
         * 활성화 된 RenderTarget을 지웁니다.
         */
        void clearRenderTarget();
        /**
         * 활성화 된 RenderTarget의 버퍼를 바꿉니다.
         */
        void swapBuffers();

    protected:
        void onStartUp() override;
        void onShutDown() override;
    };
}
