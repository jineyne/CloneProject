#pragma once

#include "cpf.hpp"

#include "Manager/ObjectManager.hpp"
#include "Scene/Object.hpp"

namespace cpf {
    class DLL_EXPORT Actor : public Object {
    private:
        std::vector<Actor *> mChildActorList {};
        std::vector<Component *> mAttachedComponentList {};
        Actor *mParentActor = nullptr;

    public:
        Actor(const String &name, uint32_t flags = 0x0);
        virtual ~Actor();

    public:
        bool operator==(Actor *actor);

    public:
        void startUp();
        void shutDown();
        void update();

        void destroy(bool immediate = false) override;

        void setParent(Actor *actor);
        
        void addChild(Actor *actor);
        void removeChild(Actor *actor);

        void attachComponent(Component *component);

        template<typename T> T *addComponenet(const String &name) {
            static_assert(std::is_base_of<Component, T>::value, "Add component type is not derived from component!");

            T *component = Allocator::New<T>(this, std::forward<Args>(args)...);
            ObjectManager::Instance().registerObject(component);

            attachComponent(component);

            return compnent;
        }

        template<typename T> T *getComponenet() {
            for (auto component : mAttachedComponentList) {
                if (component->getThisClass() == T::GetRuntimeClass()) {
                    return component;
                }
            }

            return nullptr;
        }

        bool equals(Actor *actor) const;

    protected:
        // @copydoc Object::initialize
        void initialize(uint32_t id) override;

        // @copydoc Object::destroyInternal
        void destroyInternal(bool immediate = false) override;

        virtual void onStartUp() {}
        virtual void onShutDown() {}
        virtual void onUpdate() {}

        DECL_RUNTIMECLASS(Actor);
    };
}
