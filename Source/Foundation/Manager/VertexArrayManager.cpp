#include "VertexArrayManager.hpp"

#include "RenderAPI/Utility.hpp"
#include "RenderAPI/VertexBuffer.hpp"

#define VBO_BUFFER_OFFSET(i) ((char *)NULL + (i))

namespace cpf {
    VertexArray::VertexArray(GLuint arrayId, std::vector<VertexBuffer *> attachedBuffers)
        : mArrayId(arrayId), mAttachedBuffers(attachedBuffers) {}

    ::std::size_t VertexArray::Hash::operator()(const VertexArray &vao) const {
        std::size_t seed = 0;
        CombineHash(seed, vao.mVertexProgramId);

        uint32_t size = vao.mAttachedBuffers.size();
        for (uint32_t i = 0; i < size; i++) {
            CombineHash(seed, vao.mAttachedBuffers[i]->getBufferId());
        }

        return seed;
    }

    bool VertexArray::Equal::operator()(const VertexArray &a, const VertexArray &b) const {
        if (a.mVertexProgramId != b.mVertexProgramId) {
            return false;
        }

        if (a.mAttachedBuffers.size() != b.mAttachedBuffers.size()) {
            return false;
        }

        uint32_t maxSize = a.mAttachedBuffers.size();
        for (uint32_t i = 0; i < maxSize; i++) {
            if (a.mAttachedBuffers[i]->getBufferId() != b.mAttachedBuffers[i]->getBufferId()) {
                return false;
            }
        }

        return true;
    }

    bool VertexArray::operator==(const VertexArray &obj) const {
        if (mVertexProgramId != obj.mVertexProgramId) {
            return false;
        }

        if (mAttachedBuffers.size() != obj.mAttachedBuffers.size()) {
            return false;
        }

        uint32_t maxSize = mAttachedBuffers.size();
        for (uint32_t i = 0; i < maxSize; i++) {
            if (mAttachedBuffers[i]->getBufferId() != obj.mAttachedBuffers[i]->getBufferId()) {
                return false;
            }
        }

        return true;
    }

    bool VertexArray::operator!=(const VertexArray &obj) const {
        return !(*this == obj);
    }

    const VertexArray &VertexArrayManager::getVAO(const Shader *shader, const VertexDeclaration *vertexDecl, 
            const std::array<VertexBuffer *, 32> &activeBuffers) {
        const auto &decl = vertexDecl->getElements();
        uint32_t usedBufferCount = 0;
        int32_t streamToSeqIdx = -1;
        std::vector<VertexBuffer *> usedBufferList(activeBuffers.size(), nullptr);

        for (auto &elem : decl) {
            if (streamToSeqIdx != -1) {
                break;
            }

            VertexBuffer *vertexBuffer = activeBuffers[0];
            streamToSeqIdx = static_cast<uint32_t>(usedBufferCount);

            if (vertexBuffer != nullptr) {
                usedBufferList[usedBufferCount] = vertexBuffer;
            } else {
                usedBufferList[usedBufferCount] = nullptr;
            }

            usedBufferCount++;
        }

        VertexArray wantedVAO(0, usedBufferList);
        const std::vector<VertexElement> &inputAttrib = shader->getInputDeclaration()->getElements();
        
        glGenVertexArrays(1, &wantedVAO.mArrayId);
        glBindVertexArray(wantedVAO.mArrayId);

        for (auto &elem : decl) {
            if (streamToSeqIdx == -1) {
                continue;
            }

            bool foundSemantic = false;
            GLint attribLoc = 0;
            
            for (auto it = inputAttrib.begin(); it != inputAttrib.end(); it++) {
                if (it->getSemantic() == elem.getSemantic()) {
                    foundSemantic = true;
                    attribLoc = it->getOffset();
                    break;
                }
            }

            if (!foundSemantic) {
                continue;
            }

            auto *buffer = activeBuffers[streamToSeqIdx];
            glBindBuffer(GL_ARRAY_BUFFER, buffer->getBufferId());

            void *bufferData = VBO_BUFFER_OFFSET(elem.getOffset());

            uint16_t typeCount = VertexElement::GetTypeCount(elem.getType());
            GLenum glType = GL::GetType(elem.getType());
            bool isInteger = glType == GL_SHORT || glType == GL_UNSIGNED_SHORT || glType == GL_INT ||
                             glType == GL_UNSIGNED_INT || glType == GL_UNSIGNED_BYTE;

            GLboolean normalized = GL_FALSE;

            GLsizei vertexSize = static_cast<GLsizei>(buffer->getSize());
            if (isInteger) {
                glVertexAttribIPointer(attribLoc, typeCount, glType, vertexSize, bufferData);
            } else {
                glVertexAttribPointer(attribLoc, typeCount, glType, normalized, vertexSize, bufferData);
            }

            glVertexAttribDivisor(attribLoc, elem.getInstanceStepRate());
            glEnableVertexAttribArray(attribLoc);
        }

        wantedVAO.mAttachedBuffers.assign(activeBuffers.begin(), activeBuffers.begin() + usedBufferCount);
        for (uint32_t i = 0; i < usedBufferCount; i++) {
            wantedVAO.mAttachedBuffers[i] = activeBuffers[i];
            // usedBuffers[i]->registerVAO(wantedVAO);
        }

        auto it = mVertexArrayList.insert(wantedVAO);

        return *it.first;
    }
}
