#pragma once

#include "cpf.hpp"

#include "Manager/ObjectManager.hpp"
#include "Scene/Actor.hpp"

namespace cpf {
    /**
     * 씬에 관련된 정보를 보유하고있는 클래스입니다.
     */
    class DLL_EXPORT Scene {
    private:
        String mSceneName; //< 장면 이름
        Actor *mRootActor; //< 최상위 액터

    public:
        Scene(const String &name);
        ~Scene();

    public:
        /**
         * 특정 Actor를 해당 장면에 생성합니다.
         */
        template <typename T = Actor>
        T *spawnActor(const String &name) {
            static_assert(std::is_base_of<Actor, T>::value, "spawn actor type is must be derived from actor!");
            T *actor = Allocator::New<T>(name);

            ObjectManager::Instance().registerObject(actor);
            mRootActor->addChild(actor);

            return actor;
        }

    protected:
        virtual void onStartUp() {};
        virtual void onShutDown() {};
        virtual void onUpdate() {};

    private:
        friend class SceneManager;

        void startUp();
        void shutDown();
        void update();
    };
}
