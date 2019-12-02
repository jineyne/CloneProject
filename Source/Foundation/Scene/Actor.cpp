#include "Actor.hpp"

#include "Manager/ObjectManager.hpp"

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

        for (auto actor : mChildActorList) {
            actor->startUp();
        }
    }

    void Actor::shutDown() {
        onShutDown();

        for (auto actor : mChildActorList) {
            actor->shutDown();
        }
    }

    void Actor::update() {
        onUpdate();

        for (auto actor : mChildActorList) {
            actor->update();
        }
    }

    void Actor::destroy(bool immediate) {
        destroyInternal(immediate);

        Object::destroy(immediate);
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

    bool Actor::equals(Actor *actor) const {
        return actor != nullptr && getId() == actor->getId();
    }

    void Actor::initialize(uint32_t id) {
        Object::initialize(id);
    }

    void Actor::destroyInternal(bool immediate) {
        if (immediate) {
            // TODO: doing something
            
            ObjectManager::Instance().unregisterObject(this);
        } else {
            ObjectManager::Instance().queueForDestroy(this);
        }
    }
}
