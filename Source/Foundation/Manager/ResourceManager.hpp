#pragma once

#include "cpf.hpp"

#include "Mesh/Mesh.hpp"
#include "Resource/Resource.hpp"

#include "Utility/Module.hpp"

namespace cpf {
    class DLL_EXPORT ResourceManager : public TModule<ResourceManager> {
    private:
        std::unordered_map<String, Resource> mLoadedResourceList;

        Mesh *mSpriteMesh;

    public:
        ResourceManager() = default;
        
    public:
        template<class T, typename ...Args> T *load(Args&&...args);

        Mesh *getSpriteMesh() const { return mSpriteMesh; }

    protected:
        void onStartUp() override;
        void onShutDown() override;
    };
}
