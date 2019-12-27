#pragma once

#include "cpf.hpp"

#include "Utility/Flags.hpp"
#include "Utility/RuntimeClass.hpp"

namespace cpf {
    enum class ETransformChangedFlags {
        None = 1 << 0,
        Transform = 1 << 1,
        Parent = 1 << 2,
        Mobility = 1 << 3,
    };
    using TransformChangedFlags = Flags<ETransformChangedFlags>;

    class DLL_EXPORT Object {
    protected:
        uint32_t mObjectId;

        // TODO: Change to StringId
        String mName;
        bool mActiveSelf = true;

        bool mIsInitialize = false;
        bool mIsDestroyed = false;

    public:
        Object(const String &name, uint32_t flags);

    public:
        virtual void destroy(bool immediate = false);

        void setActive(bool active);
        bool isActive() const;

        String getName() const { return mName; }

        uint32_t getId() const { return mObjectId; }

        bool isInitialize() const;
        bool isDestroyed() const;

    protected:
        virtual void initialize(uint32_t id);
        virtual void destroyInternal(bool immediate = false) = 0;

    private:
        friend class ObjectManager;

        DECL_RUNTIMECLASS(Object);
    };
}
