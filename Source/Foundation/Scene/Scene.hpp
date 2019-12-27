#pragma once

#include "cpf.hpp"

#include "Manager/ObjectManager.hpp"
#include "Scene/Actor.hpp"

namespace cpf {
    class DLL_EXPORT Scene {
    private:
        String mSceneName;
        Actor *mRootActor;

    public:
        Scene(const String &name);
        ~Scene();

    public:
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
