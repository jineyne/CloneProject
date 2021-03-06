#include "Actor.hpp"

#include "Manager/ObjectManager.hpp"
#include "Scene/Component.hpp"

namespace cpf {
    IMPL_RUNTIMECLASS(Actor, Object);

    Actor::Actor(const String &name, uint32_t flags) : Object(name, flags) {}

    Actor::~Actor() {
        if (!isDestroyed()) {
            Debug::LogWarning("Object is begin deleted without being destroyed first: {}", mName);

            destroyInternal(true);
        }
    }

    bool Actor::operator==(Actor *actor) {
        return equals(actor);
    }

    void Actor::startUp() {
        onStartUp();

        for (auto component : mAttachedComponentList) {
            component->onStartUp();
        }
        
        for (auto actor : mChildActorList) {
            actor->startUp();
        }
    }

    void Actor::shutDown() {
        onShutDown();

        for (auto component : mAttachedComponentList) {
            component->onShutDown();
        }

        for (auto actor : mChildActorList) {
            actor->shutDown();
            actor->destroy();
        }
    }

    void Actor::update() {
        onUpdate();

        for (auto component : mAttachedComponentList) {
            component->onUpdate();
        }

        for (auto actor : mChildActorList) {
            actor->update();
        }
    }

    void Actor::destroy(bool immediate) {
        destroyInternal(immediate);

        Object::destroy(immediate);
    }

    const Transform &Actor::getTransform() const {
        if (isCachedWorldTransformUpToDate()) {
            updateWorldTransform();
        }

        return mWorldTransform;
    }

    const Transform &Actor::getLocalTransform() const {
        if (isCachedLocalTransformUpToDate()) {
            updateLocalTransform();
        }

        return mLocalTransform;
    }

    void Actor::setWorldPosition(const Vector3 &pos) {
        mWorldTransform.setPosition(pos);
        notifyTransformChanged(ETransformChangedFlags::Transform);
    }

    void Actor::setWorldRotation(const Quaternion &rot) {
        mWorldTransform.setRotation(rot);
        notifyTransformChanged(ETransformChangedFlags::Transform);
    }

    void Actor::setWorldScale(const Vector3 &scale) {
        mWorldTransform.setScale(scale);
        notifyTransformChanged(ETransformChangedFlags::Transform);
    }

    const Matrix4 &Actor::getLocalMatrix() const {
        if (isCachedLocalTransformUpToDate()) {
            updateLocalTransform();
        }

        return mCachedLocalTransform;
    }

    const Matrix4 &Actor::getWorldMatrix() const {
        if (isCachedWorldTransformUpToDate()) {
            updateWorldTransform();
        }

        return mCachedWorldTransform;
    }

    void Actor::move(const Vector3 &vec) {
        mLocalTransform.move(vec);
        notifyTransformChanged(ETransformChangedFlags::Transform);
    }

    void Actor::rotate(const Quaternion &quat) {
        mLocalTransform.rotate(quat);
        notifyTransformChanged(ETransformChangedFlags::Transform);
    }
    void Actor::scale(const Vector3 &scl) {
        mLocalTransform.scale(scl);
        notifyTransformChanged(ETransformChangedFlags::Transform);
    }

    void Actor::setParent(Actor *actor) {
        if (mParentActor == actor) {
            return;
        }

        mParentActor = actor;
    }

    void Actor::addChild(Actor *actor) {
        if (actor->mParentActor == this) {
            return;
        }

        mChildActorList.push_back(actor);
        actor->setParent(actor);
    }

    void Actor::removeChild(Actor *actor) {
        if (actor->mParentActor != this) {
            return;
        }

        auto it = std::find(mChildActorList.begin(), mChildActorList.end(), actor);
        if (it != mChildActorList.end()) {
            mChildActorList.erase(it);
            (*it)->setParent(nullptr);
        }
    }

    void Actor::attachComponent(Component *component) {
        auto it = std::find(mAttachedComponentList.begin(), mAttachedComponentList.end(), component);
        if (it != mAttachedComponentList.end()) {
            Debug::LogWarning("{} is already attached", component->getName());
            return;
        }

        mAttachedComponentList.push_back(component);
    }

    bool Actor::equals(Actor *actor) const {
        return actor != nullptr && getId() == actor->getId();
    }

    void Actor::initialize(uint32_t id) {
        Object::initialize(id);
    }

    void Actor::destroyInternal(bool immediate) {
        if (immediate) {
            // TODO: doing something
            while (!mChildActorList.empty()) {
                auto child = mChildActorList.back();
                mChildActorList.pop_back();

                child->destroyInternal(immediate);
                Allocator::Delete(child);
            }

            while (!mAttachedComponentList.empty()) {
                auto component = mAttachedComponentList.back();
                mAttachedComponentList.pop_back();

                component->destroy(immediate);
                Allocator::Delete(component);
            }

            mIsDestroyed = true;
            
            ObjectManager::Instance().unregisterObject(this);
        } else {
            ObjectManager::Instance().queueForDestroy(this);
        }
    }

    void Actor::updateLocalTransform() const {
        mCachedLocalTransform = mLocalTransform.getMatrix();
        mDirtyFlags.unSet(ETransformDirtyFlags::LocalTransform);
    }

    void Actor::updateWorldTransform() const {
        mWorldTransform = mLocalTransform;

        if (mParentActor != nullptr) {
            mCachedWorldTransform = mWorldTransform.getMatrix();
        } else {
            mCachedWorldTransform = getLocalMatrix();
        }
        mDirtyFlags.unSet(ETransformDirtyFlags::WorldTransform);
    }

    void Actor::notifyTransformChanged(TransformChangedFlags flags) const {
        TransformChangedFlags componentFlags = flags;
        mDirtyFlags.set(ETransformDirtyFlags::LocalTransform).set(ETransformDirtyFlags::WorldTransform);

        if (componentFlags) {
            for (auto &entry : mAttachedComponentList) {
                entry->onTransformChanged(componentFlags);
            }
        }

        flags.unSet(ETransformChangedFlags::Mobility);
        if (flags) {
            for (auto &entry : mChildActorList) {
                entry->notifyTransformChanged(flags);
            }
        }
    }
}
