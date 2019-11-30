#include "Actor.hpp"

namespace cpf {
    IMPL_RUNTIMECLASS(Actor, Object);

    Actor::Actor(const String &name, uint32_t flags) : Object(name, flags) {}

    Actor::~Actor() {
        if (!isDestroyed()) {
            Debug::LogWarning("Object is begin deleted without being destroyed first: {}", mName);

            destroyInternal(true);
        }
    }

    void Actor::destroy(bool immediate) {
        destroyInternal(immediate);

        Object::destroy(immediate);
    }

    void Actor::initialize(uint32_t id) {
        Object::initialize(id);
    }

    void Actor::destroyInternal(bool immediate) {
        if (immediate) {
            // ActorManager::Instance().unregisterObject(this);
        } else {
            // ActorManager::Instance().queueForDestroy(this);
        }
    }
}
