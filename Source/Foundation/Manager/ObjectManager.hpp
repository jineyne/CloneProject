#pragma once

#include "cpf.hpp"

#include "Scene/Object.hpp"
#include "Utility/Module.hpp"

namespace cpf {
    /**
     * Object 클래스 및 하위 클래스를 관장하는 모듈입니다.
     */
    class DLL_EXPORT ObjectManager : public TModule<ObjectManager> {
    private:
        static uint32_t NextId;

        std::map<uint32_t, Object *> mRegistedObjectList; //< 생성된 오브젝트들입니다.
        std::queue<Object *> mQueuedObjectList; //< 오브젝트 삭제 대기열입니다.

    public:
        /**
         * 오브젝트를  등록합니다.
         */
        void registerObject(Object *object);

        /**
         * 오브젝트를 등록 해제힙니다.
         */
        void unregisterObject(Object *object);

        /**
         * 해당 아이디를 가진 오브젝트를 반환합니다.
         */
        Object *getObject(uint32_t id);

        /**
         * 오브젝트를 삭제 대기열에 추가합니다.
         */
        void queueForDestroy(const Object *object);

        /**
         * 오브젝트를 삭제합니다.
         */
        void destroyQueuedObject();
    };
}
