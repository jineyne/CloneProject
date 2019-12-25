#pragma once

#include "cpf.hpp"

#include "Mesh/Mesh.hpp"
#include "RenderAPI/Shader.hpp"

namespace cpf {
    class DLL_EXPORT Renderable {
    protected:
        Mesh *mMesh;
        Shader *mShader;

    public:
        Renderable();
        virtual ~Renderable();

    public:
        void setMesh(Mesh *mesh);
        Mesh *getMesh() const;

        void setShader(Shader *shader);
        Shader *getShader() const;

        virtual void updateShaderData(Shader *shader) = 0;
    };
}
