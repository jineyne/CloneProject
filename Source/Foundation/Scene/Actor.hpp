#pragma once

#include "cpf.hpp"

#include "Scene/Object.hpp"

namespace cpf {
    class DLL_EXPORT Actor : public Object {
    public:
        Actor(const String &name, uint32_t flags = 0x0);
        virtual ~Actor();

    public:
        void destroy(bool immediate = false) override;

    protected:
        // @copydoc Object::initialize
        void initialize(uint32_t id) override;

        // @copydoc Object::destroyInternal
        void destroyInternal(bool immediate = false) override;

        DECL_RUNTIMECLASS(Actor);
    };
}
