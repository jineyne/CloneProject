#include "RuntimeClass.hpp"

namespace cpf {
    uint32_t RuntimeClass::NextId = 1;

    RuntimeClass::RuntimeClass(String className, const RuntimeClass *base) 
        : mClassName(className), mBaseClass(const_cast<RuntimeClass *>(base)) {
        mClassId = NextId++;
    }

    bool RuntimeClass::operator==(const RuntimeClass *rhs) {
        return mClassId == rhs->mClassId;
    }

    bool RuntimeClass::isDerivedFrom(const RuntimeClass *base) const {
        if (mBaseClass == nullptr) {
            return false;
        } 

        if (mBaseClass == base) {
            return true;
        }

        return mBaseClass->isDerivedFrom(base);
    }
}
