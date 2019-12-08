#include "VertexDataDesc.hpp"

namespace cpf {
    void VertexDataDesc::addElement(VertexElementType type, VertexElementSemantic semantic, uint32_t semanticIdx,
            uint32_t instanceStepRate) {
        mElementList.emplace_back(0, type, semantic, semanticIdx, instanceStepRate);
    }

    uint32_t VertexDataDesc::getElementSize(VertexElementSemantic semantic) const {
        for (auto &element : mElementList) {
            if (element.getSemantic() == semantic) {
                return element.getSize();
            }
        }

        return -1;
    }

    uint32_t VertexDataDesc::getVertexStride() const {
        uint32_t vertexStride = 0;
        for (auto &element : mElementList) {
            vertexStride += element.getSize();
        }

        return vertexStride;
    }

    const VertexElement *VertexDataDesc::getElement(VertexElementSemantic semantic) const {
        for (auto &element : mElementList) {
            if (element.getSemantic() == semantic) {
                return &element;
            }
        }

        return nullptr;
    }

    std::vector<VertexElement> VertexDataDesc::createElements() const {
        std::vector<VertexElement> declarationElements;
        uint32_t offset = 0;
        for (auto &element : mElementList) {
            declarationElements.emplace_back(offset, element.getType(), element.getSemantic(), element.getSemanticIdx(),
                                             element.getInstanceStepRate());
            offset += element.getSize();
        }
        return declarationElements;
    }
}
