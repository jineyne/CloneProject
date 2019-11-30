#include "Object.hpp"

namespace cpf {
    IMPL_RUNTIMECLASS_NP(Object);

    Object::Object(const String &name, uint32_t flags) : mName(name) {}

    void Object::destroy(bool immediate) {
        mIsDestroyed = true;
    }

    void Object::setActive(bool active) {
        mActiveSelf = active;
    }

    bool Object::isActive() const {
        return mActiveSelf;
    }

    bool Object::isDestroyed() const {
        return mIsDestroyed;
    }

    void Object::initialize(uint32_t id) {
        mObjectId = id;
    }
}
