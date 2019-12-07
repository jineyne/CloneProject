#pragma once

#include "cpf.hpp"

namespace cpf {
    enum class VertexElementSemantic {
        Position = 0,
        Color,
        TexCoord,
    };

    enum class VertexElementType {
        Float1 = 0,
        Float2,
        Float3,
        Float4,
        Int1,
        Count,
        Unknown = 0xffff,
    };

    class DLL_EXPORT VertexElement {
    private:
        VertexElementType mType;
        VertexElementSemantic mSemantic;
        uint32_t mOffset;
        uint32_t mIndex;
        uint32_t mInstanceStepRate;

    public:
        VertexElement() = default;
        VertexElement(uint32_t offset, VertexElementType type, VertexElementSemantic semantic, uint32_t index = 0,
                      uint32_t instanceStepRate = 0);

    public:
        static uint32_t GetTypeSize(VertexElementType type);
        static uint32_t GetTypeCount(VertexElementType type);
        static size_t GetHash(const VertexElement &element);

    public:
        bool operator==(const VertexElement &rhs) const;
        bool operator!=(const VertexElement &rhs) const;

        uint32_t getSize() const;
        uint32_t getOffset() const { return mOffset; }

        VertexElementType getType() const { return mType; }
        VertexElementSemantic getSemantic() const { return mSemantic; }

        uint32_t getSemanticIdx() const { return mIndex; }
        uint32_t getInstanceStepRate() const { return mInstanceStepRate; }
    };
}
