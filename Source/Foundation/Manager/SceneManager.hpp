#pragma once

#include "cpf.hpp"

#include "Scene/Scene.hpp"

#include "utility/Flags.hpp"
#include "Utility/Module.hpp"

namespace cpf {
    enum class ESceneDirtyFlags {
        SceneChanged = 1 << 0,
    };

    using SceneDirtyFlags = Flags<ESceneDirtyFlags>;

    class DLL_EXPORT SceneManager : public TModule<SceneManager> {
    private:
        Scene *mActiveScene;
        SceneDirtyFlags mDirtyFlags;

    public:
        template <typename T, typename ...Args>
        void createScene(Args&&...args) {
            Scene *scene = Allocator::New<T>(std::forward<Args>(args)...);

            loadScene(scene);
        }

        void loadScene(Scene *scene);

        void update();
    
    protected:
        void onShutDown() override;

        void unloadScene();
    };
}
