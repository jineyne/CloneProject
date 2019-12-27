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

    class DLL_EXPORT RuntimeClass {
    public:
        static uint32_t NextId;

    private:
        uint32_t mClassId;
        String mClassName;
        RuntimeClass *mBaseClass;

    public:
        RuntimeClass(String className, const RuntimeClass *baseClass);

    public:
        bool operator ==(const RuntimeClass *rhs);

    public:
        bool isDerivedFrom(const RuntimeClass *base) const;

        uint32_t getId() const { return mClassId; }
        const String &getName() const { return mClassName; }
        const RuntimeClass *getBaseClass() const { return mBaseClass; }
    };

    template<typename ToType, typename FromType>
    ToType *DynamicCast(FromType *from) {
        if (from != nullptr && FromType::GetThisClass()->isDerivedFrom(ToType::GetThisClass())) {
            return reinterpret_cast<ToType *>(from);
        } else {
            return nullptr;
        }
    }

    template<typename T>
    const RuntimeClass *TypeOf() {
        return T::GetThisClass();
    }
}
