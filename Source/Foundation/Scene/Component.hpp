#pragma once

#include "cpf.hpp"

#include "Scene/Object.hpp"
#include "Utility/RuntimeClass.hpp"

namespace cpf {
    class DLL_EXPORT Component : public Object {
    protected:
        Actor *mOwner = nullptr;

    public:
        Component(const String &name, Actor *owner);
        virtual ~Component() = default;

    public:
        virtual void onStartUp() = 0;
        virtual void onShutDown() = 0;
        virtual void onUpdate() = 0;

    protected:
        void destroyInternal(bool immediate = false) override;

    private:
        friend class Actor;

        DECL_RUNTIMECLASS(Component);
    };
}
