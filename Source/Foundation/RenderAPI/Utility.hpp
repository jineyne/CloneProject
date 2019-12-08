#pragma once

#include "cpf.hpp"

#include "RenderAPI/VertexDeclaration.hpp"

namespace cpf {
    class DLL_EXPORT GL {
    public:
        static GLenum GetType(VertexElementType type) {
            switch(type) {
            case VertexElementType::Float1:
            case VertexElementType::Float2:
            case VertexElementType::Float3:
            case VertexElementType::Float4:
                return GL_FLOAT;

            case VertexElementType::Int1:
                return GL_INT;

            default:
                return 0;
            };
        }
    };
}
