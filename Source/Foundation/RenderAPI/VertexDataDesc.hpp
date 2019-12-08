#pragma once

#include "cpf.hpp"
#include "RenderAPI/VertexDeclaration.hpp"

namespace cpf {
    class DLL_EXPORT VertexDataDesc {
    private:
        std::vector<VertexElement> mElementList;

    public:
        void addElement(VertexElementType type, VertexElementSemantic semantic, uint32_t semanticIdx = 0, uint32_t instanceStepRate = 0);

        uint32_t getElementSize(VertexElementSemantic semantic) const;
        uint32_t getVertexStride() const;

        const VertexElement &getElement(uint32_t idx) const { return mElementList[idx]; }
        const VertexElement *getElement(VertexElementSemantic semantic) const;

        std::vector<VertexElement> createElements() const;
    };
}
