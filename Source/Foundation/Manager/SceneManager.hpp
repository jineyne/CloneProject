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

    /**
     * 장면을 관리하는 메니저 모듈입니다.
     */
    class DLL_EXPORT SceneManager : public TModule<SceneManager> {
    private:
        //< 현재 실행되는 장면입니다.
        Scene *mActiveScene;

        //< 장면의 변경 상황입니다.
        SceneDirtyFlags mDirtyFlags;

    public:
        /**
         * 장면을 생성하고 로드합니다.
         * @param args 장면 생성에 필요한 인자들
         */
        template <typename T, typename ...Args>
        void createScene(Args&&...args) {
            Scene *scene = Allocator::New<T>(std::forward<Args>(args)...);

            loadScene(scene);
        }

        /**
         * 이전에 생성된 장면을 해제하고 받은 장면을 불러옵니다.
         */
        void loadScene(Scene *scene);

        /**
         * 작동 중인 장면을 업데이트합니다.
         */
        void update();
    
    protected:
        void onShutDown() override;

        void unloadScene();
    };
}
