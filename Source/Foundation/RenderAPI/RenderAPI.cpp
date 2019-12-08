#include "RenderAPI.hpp"

#include "Manager/VertexArrayManager.hpp"
#include "RenderAPI/RenderWindow.hpp"

namespace cpf {
    void glfwErrorCallback(int error, const char* description) {
        Debug::LogError(description);
    }

    void RenderAPI::beginDraw() {
        if (mDrawCallInProgress) {
            Debug::LogError("Already begin draw call!");
        }

        mDrawCallInProgress = true;
        glUseProgram(mActiveShader->getProgramId());

        const auto &vao = VertexArrayManager::Instance().getVAO(mActiveShader, mVertexDeclaration, mActiveVertexBuffers);
        glBindVertexArray(vao.getArrayId());
    }

    void RenderAPI::endDraw() {
        if (!mDrawCallInProgress) {
            return;
        }

        mDrawCallInProgress = false;
    }

    void RenderAPI::setRenderTarget(RenderTarget *target) {
        /**
         * TODO:
         *  해당 RenderTarget이 Window인지 확인 후 초기화할 예정입니다
         */
        RenderWindow *window = static_cast<RenderWindow *>(target);
        glfwMakeContextCurrent(window->getWindowHandle());

        mActiveRenderTarget = target;
    }

    void RenderAPI::setVertexBuffer(uint32_t index, std::vector<VertexBuffer *> buffers) {
#if DEBUG_MODE
        if (index + buffers.size() > 32) {
            Debug::LogError("vertex buffer slot range is invalid: {} to {}", index, index + buffers.size());
            return;
        }
#endif

        for (uint32_t i = 0; i < buffers.size(); i++) {
            mActiveVertexBuffers[index + i] = buffers[i];
        }
    }

    void RenderAPI::setIndexBuffer(IndexBuffer *buffer) {
        mActiveIndexBuffer = buffer;
    }

    void RenderAPI::setShader(Shader *shader) {
        mActiveShader = shader;
    }

    void RenderAPI::setVertexDeclaration(VertexDeclaration *decl) {
        mVertexDeclaration = decl;
    }

    void RenderAPI::drawElements(uint32_t indexOffset, uint32_t indexCount, uint32_t vertexOffset, uint32_t vertexCount, 
            uint32_t instanceCount) {
        if (mActiveIndexBuffer == nullptr) {
            Debug::LogWarning("index buffer is not set");
            return;
        }

        beginDraw();

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mActiveIndexBuffer->getBufferId());

        if (instanceCount <= 1) {
            glDrawElementsBaseVertex(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 
                    (GLvoid *) (uint64_t) (mActiveIndexBuffer->getIndexSize() * indexOffset),
                    vertexOffset);
        } else {
            glDrawElementsInstancedBaseVertex(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT,
                    (GLvoid *) (uint64_t) (mActiveIndexBuffer->getIndexSize() * indexOffset),
                    instanceCount, vertexOffset);
        }

        endDraw();
    }

    void RenderAPI::clearRenderTarget() {
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void RenderAPI::swapBuffers() {
        mActiveRenderTarget->swapBuffers(0x0);
    }

    void RenderAPI::onStartUp() {
        if (!glfwInit()) {
            Debug::LogFatal("Failed to initialize glfw!");
        }

        glfwSetErrorCallback(glfwErrorCallback);
    }

    void RenderAPI::onShutDown() {
        glfwTerminate();
    }
}
