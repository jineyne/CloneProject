#pragma once

#include "cpf.hpp"

#include "Scene/Object.hpp"
#include "Utility/Module.hpp"
#include "Utility/RuntimeClass.hpp"

namespace cpf {
    class DLL_EXPORT ObjectManager : public TModule<ObjectManager> {
    private:
        static uint32_t NextId;

        std::map<uint32_t, Object *> mRegistedObjectList;
        std::queue<Object *> mQueuedObjectList;

    public:
        void registerObject(Object *object);

        void unregisterObject(Object *object);

        Object *getObject(uint32_t id);

        Object *findObjectByType(const RuntimeClass *rc);

        void queueForDestroy(const Object *object);

        void destroyQueuedObject();
    };
}
