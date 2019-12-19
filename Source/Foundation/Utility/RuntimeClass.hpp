#pragma once

#include "cpf.hpp"

namespace cpf {
#define DECL_RUNTIMECLASS(CLASS)                                    \
    public:                                                         \
        static const cpf::RuntimeClass class##CLASS;                \
    public:                                                         \
        static const cpf::RuntimeClass *GetThisClass();             \
        virtual const cpf::RuntimeClass *getRuntimeClass() const;   \

#define IMPL_RUNTIMECLASS_NP(CLASS)                                 \
    const cpf::RuntimeClass CLASS::class##CLASS = {                 \
        #CLASS, nullptr                                             \
    };                                                              \
    const cpf::RuntimeClass *CLASS::GetThisClass()                  \
    { return &CLASS::class##CLASS; }                                \
    const cpf::RuntimeClass *CLASS::getRuntimeClass() const         \
    { return &CLASS::class##CLASS; }

#define IMPL_RUNTIMECLASS(CLASS, BASE)                              \
    const cpf::RuntimeClass CLASS::class##CLASS = {                 \
        #CLASS, BASE::GetThisClass()                                \
    };                                                              \
    const cpf::RuntimeClass *CLASS::GetThisClass()                  \
    { return &CLASS::class##CLASS; }                                \
    const cpf::RuntimeClass *CLASS::getRuntimeClass() const         \
    { return &CLASS::class##CLASS; }

    /**
     * 간단한 RTTI 클래스입니다.
     *
     * @brief
     *  CRuntimeClass를 기반으로 하는 RTTI클래스
     */
    class DLL_EXPORT RuntimeClass {
    public:
        static uint32_t NextId;

    private:
        uint32_t mClassId; //< 클래스의 식별자입니다.
        String mClassName;
        RuntimeClass *mBaseClass;

    public:
        RuntimeClass(String className, const RuntimeClass *baseClass);

    public:
        bool operator ==(const RuntimeClass *rhs);

    public:
        /**
         * 해당 클래스가 주어진 런타임 클래스의 자식인지 확인합니다.
         */
        bool isDerivedFrom(const RuntimeClass *base) const;

        uint32_t getId() const { return mClassId; }
        const String &getName() const { return mClassName; }
        const RuntimeClass *getBaseClass() const { return mBaseClass; }
    };

    /**
     * RuntimeClass를 보유하는 클래스를 빠르게 캐스팅해줍니다.
     * @warning
     *  RuntimeClass를 포함하고 있는 클래스 전용입니다.
     */
    template<typename ToType, typename FromType>
    ToType *DynamicCast(FromType *from) {
        if (from != nullptr && FromType::GetThisClass()->isDerivedFrom(ToType::GetThisClass())) {
            return reinterpret_cast<ToType *>(from);
        } else {
            return nullptr;
        }
    }

    /**
     * TypeOf!
     */
    template<typename T>
    const RuntimeClass *TypeOf() {
        return T::GetThisClass();
    }
}
