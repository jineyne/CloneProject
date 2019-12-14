#pragma once

#include "cpf.hpp"

#include "Manager/ObjectManager.hpp"
#include "Scene/Object.hpp"
#include "Scene/Transform.hpp"

namespace cpf {
    enum class ETransformDirtyFlags {
        LocalTransform,
        WorldTransform,
    };
    using TransformDirtyFlags = Flags<ETransformDirtyFlags>;

    class DLL_EXPORT Actor : public Object {
    private:
        std::vector<Actor *> mChildActorList {};
        std::vector<Component *> mAttachedComponentList {};

        mutable TransformDirtyFlags mTransformDirtyFlags;

        Transform mLocalTransform;
        mutable Transform mWorldTransform;

        mutable Matrix4 mCachedLocalTransform = Matrix4(1.0f);
        mutable Matrix4 mCachedWorldTransform = Matrix4(1.0f);

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

        const Transform &getTransform() const;

        void setWorldPosition(const Vector3 &pos);
        void setWorldRotation(const Quaternion &rot);
        void setWorldScale(const Vector3 &scale);

        const Matrix4 &getWorldMatrix() const;
        const Matrix4 &getLocalMatrix() const;

        void move(const Vector3 &vec);
        void rotate(const Quaternion &quat);

        void setParent(Actor *actor);
        
        void addChild(Actor *actor);
        void removeChild(Actor *actor);

        void attachComponent(Component *component);

        template<typename T, typename ...Args> T *addComponenet(Args&&...args) {
            static_assert(std::is_base_of<Component, T>::value, "Add component type is not derived from component!");

            T *component = Allocator::New<T>(this, std::forward<Args>(args)...);
            ObjectManager::Instance().registerObject(component);

            attachComponent(component);

            return component;
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

        void updateLocalTransform() const;
        void updateWorldTransform() const;
        bool isCachedLocalTransformUpToDate() const {
            return (mTransformDirtyFlags.isSet(ETransformDirtyFlags::LocalTransform));
        }
        bool isCachedWorldTransformUpToDate() const {
            return (mTransformDirtyFlags.isSet(ETransformDirtyFlags::WorldTransform));
        }


        virtual void onStartUp() {}
        virtual void onShutDown() {}
        virtual void onUpdate() {}

        DECL_RUNTIMECLASS(Actor);
    };
}
