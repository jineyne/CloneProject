#include "Component.hpp"

#include "Manager/ObjectManager.hpp"
#include "Scene/Actor.hpp"

namespace cpf {
    IMPL_RUNTIMECLASS(Component, Object);

    Component::Component(Actor *owner, const String &name)
        : Object(name, 0x0), mOwner(owner) {
    }

    void Component::destroyInternal(bool immediate) {
        if (immediate) {
            ObjectManager::Instance().unregisterObject(this);
        } else {
            ObjectManager::Instance().queueForDestroy(this);
        }
    }
}
