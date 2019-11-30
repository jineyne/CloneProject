#include "ObjectManager.hpp"

#include "Debug/Debug.hpp"

namespace cpf {
    uint32_t ObjectManager::NextId = 1;

    void ObjectManager::registerObject(Object *object) {
        if (object->isInitialize()) {
            Debug::LogWarning("Object is already initialized: {}", object->getName());
            return;
        }

        if (object->isDestroyed()) {
            Debug::LogWarning("Try to regist object already destroyed: {}", object->getName());
            return;
        }

        uint32_t id = NextId++;
        mRegistedObjectList.insert(std::make_pair(id, object));

        object->initialize(id);
    }

    void ObjectManager::unregisterObject(Object *object) {
        auto it = mRegistedObjectList.find(object->getId());

        mRegistedObjectList.erase(object->getId());
    }

    Object *ObjectManager::getObject(uint32_t id) {
        auto it = mRegistedObjectList.find(id);

        if (it != mRegistedObjectList.end()) {
            return it->second;
        }

        return nullptr;
    }

    void ObjectManager::queueForDestroy(const Object *object) { 
        if (object->isDestroyed()) {
            Debug::LogWarning("Try to queue Object already destroyed: {}", object->getName());
            return;
        }

        mQueuedObjectList.push(const_cast<Object *>(object));
    }

    void ObjectManager::destroyQueuedObject() {
        while (!mQueuedObjectList.empty()) {
            Object *object = mQueuedObjectList.front();
            mQueuedObjectList.pop();

            object->destroyInternal(true);
            Allocator::Delete(object);
        }
    }
}
