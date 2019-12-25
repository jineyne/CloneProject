#pragma once

#include "cpf.hpp"

#include "FileSystem/FileSystem.hpp"

#include "Mesh/Mesh.hpp"
#include "Resource/Resource.hpp"

#include "Utility/Module.hpp"

namespace cpf {
    class DLL_EXPORT ResourceManager : public TModule<ResourceManager> {
    private:
        std::unordered_map<Path, Resource *> mLoadedResourceList;

        Mesh *mSpriteMesh;

    public:
        ResourceManager() = default;
        
    public:
        template<class T> T *load(const Path &path);

        Mesh *getSpriteMesh() const { return mSpriteMesh; }

    protected:
        void onStartUp() override;
        void onShutDown() override;
    };
}
