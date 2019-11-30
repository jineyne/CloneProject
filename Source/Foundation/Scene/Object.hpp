#pragma once

#include "cpf.hpp"

#include "Utility/RuntimeClass.hpp"

namespace cpf {
    /**
     * 신에 올라가는 오브젝트 클래스입니다.
     */
    class DLL_EXPORT Object {
    protected:
        uint32_t mObjectId;

        // TODO: Change to StringId
        String mName;
        bool mActiveSelf = true; //< 해당 오브젝트가 활성화 상태인지 여부

        bool mIsInitialize = false;
        bool mIsDestroyed = false;

    public:
        Object(const String &name, uint32_t flags);

    public:
        /**
         * 오브젝트를 삭제합니다.
         *
         * @param immediate 
         *  바로 삭제할 것인지 여부입니다.
         *  거짓일 경우 다음 Update 시작 전에 삭제됩니다.
         */
        virtual void destroy(bool immediate = false);

        // 활성화 상태를 변경합니다.
        void setActive(bool active);

        // 활성화 상태를 반환합니다.
        bool isActive() const;

        // 해당 오브젝트의 이름을 반환합니다.
        String getName() const { return mName; }

        // 해당 오브젝트의 아이디를 반환합니다.
        uint32_t getId() const { return mObjectId; }

        // 해당 오브젝트가 초기화되었는지 여부를 반환합니다.
        bool isInitialize() const;

        // 해당 오브젝트가 삭제 혹은 삭제 큐에 들어가있는지 여부를 반환합니다.
        bool isDestroyed() const;

    protected:
        virtual void initialize(uint32_t id);
        virtual void destroyInternal(bool immediate = false) = 0;

    private:
        friend class ObjectManager;

        DECL_RUNTIMECLASS(Object);
    };
}
