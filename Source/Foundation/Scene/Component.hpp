#pragma once

#include "cpf.hpp"

#include "Scene/Object.hpp"
#include "Utility/RuntimeClass.hpp"

namespace cpf {
    class DLL_EXPORT Component : public Object {
    protected:
        Actor *mOwner = nullptr;

    public:
        Component(Actor *owner, const String &name);
        virtual ~Component() = default;

    public:
        virtual void onStartUp() {};
        virtual void onShutDown() {};
        virtual void onUpdate() {};

    protected:
        void destroyInternal(bool immediate = false) override;

    private:
        friend class Actor;

        DECL_RUNTIMECLASS(Component);
    };
}
