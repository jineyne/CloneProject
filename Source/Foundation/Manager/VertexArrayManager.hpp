#pragma once

#include "cpf.hpp"

#include "RenderAPI/Shader.hpp"
#include "RenderAPI/VertexDeclaration.hpp"

#include "Utility/Module.hpp"

namespace cpf {
    class DLL_EXPORT VertexArray {
    private:
        class Hash{
        public:
            ::std::size_t operator()(const VertexArray& vao) const;
        };

        class Equal{
        public:
            bool operator()(const VertexArray &a, const VertexArray &b) const;
        };

    private:
        GLuint mArrayId = 0;
        uint64_t mVertexProgramId = 0;
        std::vector<VertexBuffer *> mAttachedBuffers;

    public:
        bool operator==(const VertexArray &obj) const;
        bool operator!=(const VertexArray &obj) const;

    public:
        GLuint getArrayId() const { return mArrayId; }

    private:
        VertexArray() = default;
        VertexArray(GLuint arrayId, std::vector<VertexBuffer *> attachedBuffers);

    private:
        friend class VertexArrayManager;
    };

    class DLL_EXPORT VertexArrayManager : public TModule<VertexArrayManager> {
    private:
        std::unordered_set<VertexArray, VertexArray::Hash, VertexArray::Equal> mVertexArrayList;
    public:
        const VertexArray &getVAO(const Shader *shader, const VertexDeclaration *vertexDecl, 
                const std::array<VertexBuffer *, 32> &activeBuffers);
    };
}
